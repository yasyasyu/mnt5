import sys
import subprocess

args = sys.argv

pwd_folder = r"/home/yas_yasyu/work/mnt5/" 
in_folder = pwd_folder + r"input/"
out_folder = pwd_folder + r"output/"
cmd_folder = pwd_folder + r"steiner-space-travel/"

arg_command = "./a.out"
file_number = 0
if len(args) > 1:
	file_number = args[1]
	
file = f"{str(file_number).zfill(4)}"
in_file =  f"{in_folder}{file}.txt"
out_file = f"{out_folder}{file}.txt"

cmd = f"{arg_command} < {in_file} > {out_file}"
subprocess.run(
	cmd,
	shell=True,
	cwd = pwd_folder
)

cmd = f"dotnet {cmd_folder}tester.dll judge -i {in_file} -o {out_file}"
subprocess.run(
	cmd,
	shell=True,
	cwd = pwd_folder
)