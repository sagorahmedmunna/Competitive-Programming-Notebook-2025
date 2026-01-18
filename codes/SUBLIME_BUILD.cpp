// check the gcc version and replace
// name the file -> cp.sublime-build
{ // ubuntu
	"cmd" : ["g++ -std=c++14 $file_name -o $file_base_name && timeout 4s ./$file_base_name<input.txt>output.txt"],
	"selector" : "source.c",
	"shell": true,
	"working_dir" : "$file_path"
}
{ // windows
	"cmd": ["g++.exe","-std=c++14", "${file}", "-o", "${file_base_name}.exe", "&&" , "${file_base_name}.exe<input.txt>output.txt"],
	"selector":"source.cpp",
	"shell":true,
	"working_dir":"$file_path"
}