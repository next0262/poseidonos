#!/usr/bin/env python3
import subprocess
import os
import sys
import json
sys.path.append("../")
sys.path.append("../../system/lib/")
sys.path.append("../array/")

import json_parser
import pos
import cli
import api
import pos_constant
import volume
import CREATE_VOL_BASIC_1
import CREATE_VOL_BASIC_2
import CREATE_VOL_BASIC_3
import CREATE_VOL_BASIC_4
import CREATE_VOL_BASIC_5
import CREATE_VOL_BASIC_6
import CREATE_VOL_BASIC_7

ARRAYNAME = CREATE_VOL_BASIC_1.ARRAYNAME


def check_result():
    detail = cli.list_volume(ARRAYNAME)
    expected_list = []
    expected_list.append(volume.Volume(CREATE_VOL_BASIC_1.VOL_NAME, 
        CREATE_VOL_BASIC_1.VOL_SIZE, CREATE_VOL_BASIC_1.VOL_IOPS, CREATE_VOL_BASIC_1.VOL_BW))
    expected_list.append(volume.Volume(CREATE_VOL_BASIC_2.VOL_NAME, 
        CREATE_VOL_BASIC_2.VOL_SIZE, CREATE_VOL_BASIC_2.VOL_IOPS, CREATE_VOL_BASIC_2.VOL_BW))
    expected_list.append(volume.Volume(CREATE_VOL_BASIC_3.VOL_NAME, 
        CREATE_VOL_BASIC_3.VOL_SIZE, CREATE_VOL_BASIC_3.VOL_IOPS, CREATE_VOL_BASIC_3.VOL_BW))
    expected_list.append(volume.Volume(CREATE_VOL_BASIC_4.VOL_NAME, 
        CREATE_VOL_BASIC_4.VOL_SIZE, CREATE_VOL_BASIC_4.VOL_IOPS, CREATE_VOL_BASIC_4.VOL_BW))
    expected_list.append(volume.Volume(CREATE_VOL_BASIC_5.VOL_NAME, 
        CREATE_VOL_BASIC_5.VOL_SIZE, CREATE_VOL_BASIC_5.VOL_IOPS, CREATE_VOL_BASIC_5.VOL_BW))
    expected_list.append(volume.Volume(CREATE_VOL_BASIC_6.VOL_NAME, 
        CREATE_VOL_BASIC_6.VOL_SIZE, CREATE_VOL_BASIC_6.VOL_IOPS, CREATE_VOL_BASIC_6.VOL_BW))
    expected_list.append(volume.Volume(CREATE_VOL_BASIC_7.VOL_NAME, 
        CREATE_VOL_BASIC_7.VOL_SIZE, CREATE_VOL_BASIC_7.VOL_IOPS, CREATE_VOL_BASIC_7.VOL_BW))

    data = json.loads(detail)
    actual_list = []
    for item in data['Response']['result']['data']['volumes']:
        vol = volume.Volume(item['name'], item['total'], item['maxiops'], item['maxbw'])
        actual_list.append(vol)

    if len(actual_list) != len(expected_list):
        return "fail"
    
    for actual in actual_list:
        checked = False
        for expected in expected_list:
            if actual.name == expected.name and actual.total == expected.total:
                checked = True
                break
        if checked == False:
            return "fail"
    return "pass"


def execute():
    CREATE_VOL_BASIC_1.execute()
    cli.create_volume(CREATE_VOL_BASIC_2.VOL_NAME, str(CREATE_VOL_BASIC_2.VOL_SIZE), str(CREATE_VOL_BASIC_2.VOL_IOPS), str(CREATE_VOL_BASIC_2.VOL_BW), ARRAYNAME)
    cli.create_volume(CREATE_VOL_BASIC_3.VOL_NAME, str(CREATE_VOL_BASIC_3.VOL_SIZE), str(CREATE_VOL_BASIC_2.VOL_IOPS), str(CREATE_VOL_BASIC_3.VOL_BW), ARRAYNAME)
    cli.create_volume(CREATE_VOL_BASIC_4.VOL_NAME, str(CREATE_VOL_BASIC_4.VOL_SIZE), str(CREATE_VOL_BASIC_2.VOL_IOPS), str(CREATE_VOL_BASIC_4.VOL_BW), ARRAYNAME)
    cli.create_volume(CREATE_VOL_BASIC_5.VOL_NAME, str(CREATE_VOL_BASIC_5.VOL_SIZE), str(CREATE_VOL_BASIC_2.VOL_IOPS), str(CREATE_VOL_BASIC_5.VOL_BW), ARRAYNAME)
    cli.create_volume(CREATE_VOL_BASIC_6.VOL_NAME, str(CREATE_VOL_BASIC_6.VOL_SIZE), str(CREATE_VOL_BASIC_2.VOL_IOPS), str(CREATE_VOL_BASIC_6.VOL_BW), ARRAYNAME)
    cli.create_volume(CREATE_VOL_BASIC_7.VOL_NAME, str(CREATE_VOL_BASIC_7.VOL_SIZE), str(CREATE_VOL_BASIC_2.VOL_IOPS), str(CREATE_VOL_BASIC_7.VOL_BW), ARRAYNAME)


if __name__ == "__main__":
    if len(sys.argv) >= 2:
        pos.set_addr(sys.argv[1])
    api.clear_result(__file__)
    execute()
    result = check_result()
    ret = api.set_result_manually(cli.list_volume(ARRAYNAME), result, __file__)
    pos.flush_and_kill_pos()
    exit(ret)
