require 'csv'

input = ARGV[0]

if input[-1] != '/'
	input = input + '/'
end

names = Array.new

Dir.glob("#{input}*") do |dir|
	puts dir
	file = dir.split(input)[1]
	first_name = file.split('_')[0]
	last_name = file.split('_')[1]
	if first_name.length == 10
		names.push([last_name, first_name])
	end
end

names = names.sort.reverse

CSV.open("result.csv", "wb") do |csv|
	names.each do |file|
		csv << [file[1], file[0]]
	end
end
