import os

print("请选择路径信息文件的类型")
print("1. 文本类型")
print("2. 二进制类型")
sel = int(input())
if sel == 1:
	print("请输入路径信息文件（文本类型）的文件名")
	infoName = input()
	if os.path.isfile(infoName):
		if os.path.exists("cache/") == False:
			os.mkdir("cache/")
		print("正在将文件 " + infoName + " 转换为二进制类型")
		os.system("DataManager.exe " + infoName + " cache/info.bin")
		print("转换完成")
		print("请输入查询文件的文件名")
		inputName = input()
		if os.path.isfile(inputName):
			print("正在查询最短路径")
			os.system("Main.exe cache/info.bin output.txt " + inputName)
			print("查询结束，查询结果保存于 output.txt")
		else:
			print("文件 " + inputName + " 不存在")
	else:
		print("文件 " + infoName + " 不存在")
else:
	print("请输入路径信息文件（二进制类型）的文件名")
	infoName = input()
	if os.path.isfile(infoName):
		print("请输入查询文件的文件名")
		inputName = input()
		if os.path.isfile(inputName):
			print("正在查询最短路径")
			os.system("Main.exe " + infoName +" output.txt " + inputName)
			print("查询结束，查询结果保存于 output.txt")
		else:
			print("文件 " + inputName + " 不存在")
	else:
		print("文件 " + infoName + " 不存在")
input("按回车结束...")