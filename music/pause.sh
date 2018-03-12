#!/bin/zsh
afplay_status=$(ps -clx | grep 'afplay' | awk '{print $11}')

if [[ $afplay_status == T ]];then
	killall -CONT -c "afplay"
else
	killall -STOP -c "afplay"
fi