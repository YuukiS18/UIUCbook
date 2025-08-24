clang -xc++ -E -dD -P - | sed -E '/^#/d' | tr -d '[:space:]' | md5sum | cut -c-6
# cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum
