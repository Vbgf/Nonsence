require 'csv'

file = ARGV[0]
open = 0
close = 0

if(file != nil && File.file?(file))
	CSV.open(file, "rb") do |csv|
		csv.each do |line|
			if(line[3].to_i == 6005)
				open += 1
			else
				close += 1
			end
		end
	end
end

puts "Open: #{open}"
puts "Closed: #{close}"
puts "Unsuccessfull shutdowns: #{open-close}"
