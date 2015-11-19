# 第7章の電卓について、変数を使用しない部分のみテスト

print "input expfile: "
expfile = gets.rstrip	# 電卓の入力ファイル名
expline = []
f1 = File.open(expfile, "r") do |f|
	expline = f.readlines
end

print "input resfile: "
resfile = gets.rstrip	# 電卓の出力ファイル名
resline = []
f2 = File.open(resfile, "r") do |f|
	resline = f.readlines
end

i = 0
error_count = 0
while(i < expline.length && i < resfile.length)
	exp_t = expline[i].rstrip.chomp(';')
	exp = exp_t.gsub(/(\s*)?\//, "* 1.0 /")	# 浮動小数点数になるように置換
	#exp = exp.gsub("^", "**")				# 冪乗の記号を置換

	/>\s=\s(.+)/ =~ resline[i]
	res = $1

	if(exp == nil || res == nil)
		break
	end

	exp_float = eval(exp)
	exp_int = exp_float.to_i
	if(exp_float == exp_int) # 小数かどうか
		s = sprintf("%d", exp_int)	
	else 
		s = sprintf("%g", exp_float)
	end

	puts s
	if(!res.match(/^#{s}/))
		print("failed: line", (i + 1).to_i, " -> ", exp_t, " != ", res, "\n")
		error_count += 1
	end	

	i += 1
end

printf("number of errors: %d\n", error_count)