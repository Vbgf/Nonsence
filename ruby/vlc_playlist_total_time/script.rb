require 'rexml/document'

def check_input_file
	if(ARGV[0] == nil)
		puts "Error: no arguments given!"
		return 1
	else
		if(ARGV[0][-1] == '/')
			puts "Error: program doesn't work with folders"
			return 1
		else
			if (File.exists?(ARGV[0]) && ARGV[0][-1] != '.')
				return 0
			else
				puts "Error: no such file in directory"
				return 1
			end
		end
	end
end

def	check_total_time

end

if(check_input_file == 0)
	check_total_time
end
