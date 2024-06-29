# For each .c in the current path (recursive)
for f in $(find . -name '*.c'); do
    # Extract the functions and his location with aux-info
    # Send the results to output.info
    # Send errors to /dev/null
    gcc -aux-info output.info $f 2>/dev/null
    # Extract function names from output.info excluding std headers and comments
    grep -Ev "/usr|compiled from" output.info
done
# Remove output.info
rm output.info