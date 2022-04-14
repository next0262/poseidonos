import fio
import graph
import initiator
import json
import lib
import target
import traceback
from datetime import datetime


def play(json_targets, json_inits, json_scenario):
    lib.printer.green(f"\n -- '{__name__}' has began --")

    raw_date = datetime.now()
    now_date = raw_date.strftime("%y%m%d_%H%M%S")
    skip_workload = False

    # validate arguments, 인자로 받은 json 정보가 있는지 확인
    if 0 == len(json_targets):
        lib.printer.red(" TargetError: At least 1 target has to exist")
        return
    if 0 == len(json_inits):
        lib.printer.red(" InitiatorError: At least 1 initiator has to exist")
        return
    if 0 == len(json_scenario):
        lib.printer.red(" ScenarioError: At least 1 scenario has to exist")
        return

    # target prepare, validation check 및 bringup/setup 진행
    targets = {}
    for json_target in json_targets:
        try:
            target_obj = target.manager.Target(json_target)
        except Exception as e:
            lib.printer.red(traceback.format_exc())
            return
        target_name = json_target["NAME"]

        try:
            target_obj.Prepare()
        except Exception as e:
            lib.printer.red(traceback.format_exc())
            skip_workload = True
            target_obj.ForcedExit()
            break
        targets[target_name] = target_obj

    # init prepare, validation check 및 bringup/setup 진행
    initiators = {}
    for json_init in json_inits:
        try:
            init_obj = initiator.manager.Initiator(json_init)
        except Exception as e:
            lib.printer.red(traceback.format_exc())
            skip_workload = True
            break
        init_name = json_init["NAME"]

        try:
            init_obj.Prepare()
        except Exception as e:
            lib.printer.red(traceback.format_exc())
            skip_workload = True
            break
        initiators[init_name] = init_obj

    # set test_target & check auto generate
    if not skip_workload:
        test_target = targets[next(iter(targets))]
        if "yes" != test_target.use_autogen:
            lib.printer.red(
                f"{__name__} [Error] check [TARGET][AUTO_GENERATE][USE] is 'yes' ")
            skip_workload = True

    # run workload
    if not skip_workload:
        lib.printer.green(f" fio start")

        graph_fio = graph.manager.Fio(
            f"{json_scenario['OUTPUT_DIR']}/{now_date}_normal")  # graph 객체 생성

        tc_list = [
            {"name": "1_sw", "rw": "write", "bs": "128k", "iodepth": "4", "io_size": test_target.volume_size,
                "time_based": "0", "runtime": "0", "log_avg_msec": "30000"},
            {"name": "2_sr", "rw": "read", "bs": "128k", "iodepth": "4", "io_size": "1t",
                "time_based": "1", "runtime": "60", "log_avg_msec": "2000"},
            {"name": "3_rw", "rw": "randwrite", "bs": "4k", "iodepth": "128",
                "io_size": "4t", "time_based": "1", "runtime": "60", "log_avg_msec": "2000"},
            {"name": "4_sus", "rw": "randwrite", "bs": "4k", "iodepth": "128", "io_size": "4t",
                "time_based": "1", "runtime": "28800", "log_avg_msec": "576000"},
            {"name": "5_rw", "rw": "randwrite", "bs": "4k", "iodepth": "128",
                "io_size": "4t", "time_based": "1", "runtime": "600", "log_avg_msec": "20000"},
            {"name": "6_rr", "rw": "randread", "bs": "4k", "iodepth": "128",
                "io_size": "4t", "time_based": "1", "runtime": "600", "log_avg_msec": "20000"},
            {"name": "7_mix", "rw": "randrw", "rwmixread": "70", "bs": "16k", "iodepth": "32",
                "io_size": "4t", "time_based": "1", "runtime": "600", "log_avg_msec": "20000"}
        ]

        for tc in tc_list:
            fio_cmdset = []
            for key in initiators:
                test_init = initiators[key]
                test_fio = fio.manager.Fio(
                    test_init.id, test_init.pw, test_init.nic_ssh)  # fio 객체 생성
                test_fio.opt["numjobs"] = "1"
                test_fio.opt["thread"] = "1"
                test_fio.opt["ioengine"] = f"{test_init.spdk_dir}/examples/nvme/fio_plugin/fio_plugin"
                test_fio.opt["ramp_time"] = "0"
                test_fio.opt["runtime"] = tc["runtime"]
                test_fio.opt["time_based"] = tc["time_based"]
                test_fio.opt["verify"] = "0"
                test_fio.opt["serialize_overlap"] = "1"
                test_fio.opt["direct"] = "1"
                test_fio.opt["size"] = "100%"
                test_fio.opt["readwrite"] = tc["rw"]
                if "randrw" == tc["rw"]:
                    test_fio.opt["rwmixread"] = tc["rwmixread"]
                else:
                    if test_fio.opt.get("rwmixread"):
                        del test_fio.opt["rwmixread"]
                test_fio.opt["bs"] = tc["bs"]
                test_fio.opt["iodepth"] = tc["iodepth"]
                test_fio.opt["io_size"] = tc["io_size"]
                test_fio.opt["output"] = f"{test_init.output_dir}/{now_date}_{tc['name']}_{test_init.name}"
                # eta graph를 그리려면 해당 옵션이 필요
                test_fio.opt["eta"] = "always"
                # 현재는 group_reporting만 지원
                test_fio.opt["group_reporting"] = "1"
                # 결과를 parsing 하기 위한 필수 옵션
                test_fio.opt["output-format"] = "json"
                # write_xxx_log option이 동작하기 위한 필수 옵션
                test_fio.opt["per_job_logs"] = "1"
                # write_xxx_log의 첫 번째 열이 epoch 시간으로 출력
                test_fio.opt["log_unix_epoch"] = "1"
                # write_xxx_log가 출력되는 주기
                test_fio.opt["log_avg_msec"] = tc["log_avg_msec"]
                test_fio.opt["write_bw_log"] = f"{test_fio.opt['output']}"
                test_fio.opt["write_iops_log"] = f"{test_fio.opt['output']}"
                test_fio.opt["write_lat_log"] = f"{test_fio.opt['output']}"
                for subsys in test_target.subsystem_list:
                    if subsys[0] == test_init.name:
                        test_fio.jobs.append(
                            f" --name=job_{subsys[2]} --filename=\"trtype={test_target.spdk_tp} adrfam=IPv4 traddr={subsys[3]} trsvcid={subsys[4]} subnqn={subsys[1]} ns=1\"")
                if not test_fio.Prepare():
                    skip_workload = True
                    break
                fio_cmdset.append(test_fio.cmd)

            if not skip_workload:
                # run fio
                try:
                    print(f" run -> {now_date}_fio_{tc['name']}")
                    fio.manager.parallel_run(fio_cmdset)
                except Exception as e:
                    lib.printer.red(f"{__name__} [Error] {e}")
                    skip_workload = True
                # copy fio result
                try:
                    for key in initiators:
                        test_init = initiators[key]
                        lib.subproc.sync_run(
                            f"sshpass -p {test_init.pw} scp {test_init.id}@{test_init.nic_ssh}:{test_init.output_dir}/{now_date}_{tc['name']}_{test_init.name}.eta {json_scenario['OUTPUT_DIR']}")
                        lib.subproc.sync_run(
                            f"sshpass -p {test_init.pw} scp {test_init.id}@{test_init.nic_ssh}:{test_init.output_dir}/{now_date}_{tc['name']}_{test_init.name} {json_scenario['OUTPUT_DIR']}")
                        lib.subproc.sync_run(
                            f"sshpass -p {test_init.pw} scp {test_init.id}@{test_init.nic_ssh}:{test_init.output_dir}/{now_date}_{tc['name']}_{test_init.name}*.log {json_scenario['OUTPUT_DIR']}/log")
                except Exception as e:
                    lib.printer.red(f"{__name__} [Error] {e}")
                    skip_workload = True
                # parsing data & draw graph
                try:
                    for key in initiators:
                        test_init = initiators[key]
                        # Eta
                        if "1_sw" != tc["name"] and "4_sus" != tc["name"]:
                            graph_fio.AddEtaData(
                                f"{json_scenario['OUTPUT_DIR']}/{now_date}_{tc['name']}_{test_init.name}.eta", f"{tc['name']}_{test_init.name}")
                            graph_fio.DrawEta(
                                ["bw_read", "bw_write", "iops_read", "iops_write"])
                        # Result
                        graph_fio.AddResultData(
                            f"{json_scenario['OUTPUT_DIR']}/{now_date}_{tc['name']}_{test_init.name}", f"{tc['name']}_{test_init.name}")
                        graph_fio.DrawResult()
                        # Log
                        graph_fio.AddLogData(
                            f"{json_scenario['OUTPUT_DIR']}/log", f"{now_date}_{tc['name']}_{test_init.name}")
                        graph_fio.DrawLog(
                            f"{json_scenario['OUTPUT_DIR']}/{now_date}_{tc['name']}_{test_init.name}")
                        graph_fio.ClearLogData()
                except Exception as e:
                    lib.printer.red(f"{__name__} [Error] {e}")
                    # skip_workload = True

        lib.printer.green(f" fio end")

    # init wrapup
    for key in initiators:
        try:
            initiators[key].Wrapup()
        except Exception as e:
            lib.printer.red(traceback.format_exc())
            skip_workload = True

    # target warpup
    for key in targets:
        try:
            targets[key].Wrapup()
        except Exception as e:
            lib.printer.red(traceback.format_exc())
            targets[key].ForcedExit()
            skip_workload = True

    if skip_workload:
        lib.printer.red(f" -- '{__name__}' unexpected done --\n")
    else:
        lib.printer.green(f" -- '{__name__}' successfully done --\n")
