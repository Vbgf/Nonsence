$count = 0
def reopen_folder (dir)
	Dir.glob(dir + '*') do |path|
		$count += 1
		if File.directory?(path)
			path = path + "/*"
			reopen_folder path
		end
	end
end

def main
	if ARGV[0] != nil
		if ARGV[0][-1] != '/' 
			ARGV[0] = ARGV[0] + '/'
		end
		reopen_folder (ARGV[0])
		puts $count
	else
		puts "Error: No arguments given"
	end
end

main
