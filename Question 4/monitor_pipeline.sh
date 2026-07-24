#!/bin/bash

# Command Pipeline to monitor logs, extract errors, save them, and suppress junk
tail -f /var/log/syslog 2>/dev/null | grep --line-buffered "ERROR" | tee -a error_report.txt
