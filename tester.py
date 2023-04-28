import sys
import subprocess

args = sys.argv

run_cmd = "n"
file_number = 0
if len(args) > 1:
	if args[1].isdecimal():
		file_number = args[1]
		if len(args) > 2:
			if not args[2].isdecimal():
				run_cmd = args[2]
			else:
				run_cmd = "p"
		else:
			run_cmd = "n"
	else:
		run_cmd = args[1]
		if len(args) > 2:
			if args[2].isdecimal():
				file_number = args[2]
			else:
				run_cmd = "p"


pwd_folder = r"/home/yas_yasyu/work/mnt5/" 
in_folder = pwd_folder + r"input/"
out_folder = pwd_folder + r"output/"
cmd_folder = pwd_folder + r"steiner-space-travel/"

arg_command = "'python3 main.py'"
file = f"{str(file_number).zfill(4)}"
in_file =  f"{in_folder}{file}.txt"
out_file = f"{out_folder}{file}.txt"
img_folder = "img/"
img_file = f"{pwd_folder}{img_folder}{file}.png"

def run(cmd):
	print(cmd)
	subprocess.run(
		cmd,
		shell=True,
		cwd = pwd_folder
	)
def normal():
	cmd = f"{arg_command} < {in_file} > {out_file}"
	run(cmd)
	cmd = f"dotnet {cmd_folder}tester.dll judge -i {in_file} -o {out_file}"
	run(cmd)

def vis():
	cmd = f"{arg_command} < {in_file} > {out_file}"
	run(cmd)
	cmd = f"dotnet {cmd_folder}tester.dll judge -i {in_file} -o {out_file} -v {img_file}"
	run(cmd)

def all():
	parallel = 8
	cmd = f"dotnet {cmd_folder}tester.dll judge-all -i {in_folder} -c {arg_command} -p {parallel}"
	subprocess.run(
		cmd,
		shell=True,
		cwd = pwd_folder
	)


def panic():
	print("python3 tester.py $cmd")
	print('$cmd : v 10')
	print('$cmd : 10')
	print('$cmd : a')

	exit()

if not run_cmd in "nvap":
	panic()

run_act = {
	"n": normal,
	"v": vis,
	"a": all,
	"p": panic
}

run_act[run_cmd]()