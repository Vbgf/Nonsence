def reopen_folder (argv)
	Dir.glob("#{argv}*") do |path|
		puts path
		if(File.directory?(path))
			reopen_folder("#{argv}/*")
		end
	end
end

def main
	if(ARGV[0] == nil)
		puts "Argument error: no arguments given!"
		return;
	end
	if(ARGV[0][-1] != '/')
		ARGV[0] = ARGV[0] + '/'
	end
	reopen_folder(ARGV[0])
end
main
