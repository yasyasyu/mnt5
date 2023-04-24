import subprocess

pwd_folder = r"/home/yas_yasyu/work/mnt5/" 
in_folder = pwd_folder + r"input/"
out_folder = pwd_folder + r"output/"
cmd_folder = pwd_folder + r"steiner-space-travel/"

arg_command = "./a.out"
file = f"{'0'.zfill(4)}"
in_file =  f"{in_folder}{file}.txt"
out_file = f"{out_folder}{file}.txt"

# dotnet tester.dll judge-all -i input -c "cmd" -p parallel
parallel = 8
cmd = f"dotnet {cmd_folder}tester.dll judge-all -i {in_folder} -c {arg_command} -p {parallel}"
subprocess.run(
	cmd,
	shell=True,
	cwd = pwd_folder
)
