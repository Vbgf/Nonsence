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
	total_time = 0
	f = File.open(ARGV[0], "r")
	f.each_line do |line|
		line = line.split("<duration>")[1]
		if (line != nil)
			line = line.split("</duration>")[0]
			total_time = total_time + line.to_i
		end	
	end
	f.close
	return total_time
end

def print_time (time)
	#time is in miliseconds so /1000
	time = time/1000
	print "#{time%60} seconds, "
	time = time/60
	print "#{time%60} minutes, "
	time = time/60
	print "#{time%24} hours, "
	time = time/24
	puts "#{time} days"
end

def main
	if(check_input_file == 0)
		print_time (check_total_time)
	end
end

main
