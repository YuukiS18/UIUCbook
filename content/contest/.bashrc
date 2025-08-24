alias c='g++ -Wall -Wconversion -Wfatal-errors -Wno-shadow -g -std=c++20 -fsanitize=undefined,address'
h() {
	cpp -dD -P "$1" | sed -E '/^#/d' | tr -d '[:space:]' | md5sum | cut -c-6
}
xmodmap -e 'clear lock' -e 'keycode 66=less greater' #caps = <>
