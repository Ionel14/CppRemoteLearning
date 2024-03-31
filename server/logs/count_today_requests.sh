#!/bin/bash

TODAY=$(date "+%Y%m%d")

grep "DATE: $TODAY" requests_log.txt | wc -l
