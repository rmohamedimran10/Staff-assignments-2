#!/bin/bash

# 1. List all hidden files to locate the swap file created by the crash
ls -a 

# 2. Use the recover flag in vi to restore the un-saved configuration file
vi -r critical_config.conf

# 3. After saving inside vi (:wq), remove the lingering swap file to prevent future warnings
rm .critical_config.conf.swp
