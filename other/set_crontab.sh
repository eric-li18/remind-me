
if [ $# -ne 1 ]; then
    echo -e "Invalid num of args\n"
else if [ "$1" = "-e" ]; then
    (crontab -l 2>/dev/null; echo MAILTO=\"\"; echo "* * * * * cd /mnt/c/Users/Eric/Documents/github/remind-me && ./monitor") | crontab -
else if [ "$1" = "-b" ]; then
    (crontab -l 2>/dev/null; echo MAILTO=\"\"; echo "* * * * * cd Desktop/remind-me && ./monitor") | crontab -
else
    echo -e "Enter option -e for eric or -b for bryan\n"
fi
