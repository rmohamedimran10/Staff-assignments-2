#!/bin/bash

# Define directories and files
SOURCE_DIR="./submissions"
BACKUP_DIR="./unique_backups"
REPORT_FILE="report.txt"
ERROR_FILE="errors.log"

# 1. Setup: Create backup directory and clear old logs. 
# Any errors (like permission issues) go to errors.log.
mkdir -p "$BACKUP_DIR" 2>> "$ERROR_FILE"
> "$REPORT_FILE"
> "$ERROR_FILE"

# Initialize counters
processed=0
duplicated=0
backed_up=0

# Create a temporary file to track file hashes
seen_hashes=$(mktemp)

echo "Processing student submissions..."

# Loop through all files in the submissions directory
for file in "$SOURCE_DIR"/*; do
    # Skip if it's not a standard file
    [ -f "$file" ] || continue
    
    ((processed++))

    # Calculate MD5 hash to check file content. Send errors to error log.
    file_hash=$(md5sum "$file" 2>> "$ERROR_FILE" | awk '{print $1}')

    # 2. Identify duplicates by checking if we've seen this hash before
    if grep -q "^$file_hash$" "$seen_hashes"; then
        ((duplicated++))
    else
        # 3. Create a backup of unique submissions
        echo "$file_hash" >> "$seen_hashes"
        cp "$file" "$BACKUP_DIR/" 2>> "$ERROR_FILE"
        ((backed_up++))
    fi
done

# Cleanup temporary file
rm -f "$seen_hashes"

# 4. Generate the final report
{
    echo "--- Submission Processing Report ---"
    echo "Files Processed: $processed"
    echo "Duplicates Found: $duplicated"
    echo "Unique Files Backed Up: $backed_up"
} > "$REPORT_FILE" 2>> "$ERROR_FILE"

echo "Processing complete. Check $REPORT_FILE for stats."
