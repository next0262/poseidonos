target_fabric_ip=127.0.0.1
pos_working_dir="$1" #추후 수정

rebuild_result=0
cd ${pos_working_dir}/test/regression/; sudo ./fault_tolerance_ci_test.sh -f ${target_fabric_ip} -i 1
if [ $? -ne 0 ];
then
    rebuild_result=1
fi

if [ $rebuild_result -eq 0 ];
then
    echo "Rebuild Test Success"
    cd ${pos_working_dir}/test/regression/; sudo echo 0 > rebuildtest
    exit 0
else
    echo "\033[1;41mRebuild Test Failed\033[0m" 1>&2
    cd ${pos_working_dir}/test/regression/; sudo echo 1 > rebuildtest
    exit 1
fi
