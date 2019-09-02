if [ $# -ne 2 ] ; then
    echo "usage: send_text [to number] [message]" ; 
else
    account_sid=ACb435abef08d8606d30db6d6b37eaece0 ; 
    auth_token=73174414c1b7c53da1f130a573cebf1a ; 
    bin/c_sms -a $account_sid -s $auth_token -t $1 -f "+6476948262" -m "$2" ; 
fi