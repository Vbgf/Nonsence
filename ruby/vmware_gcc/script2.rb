require "net/http"
require "uri"
require "set"

def format_objects(string)
	hash = Hash.new
	temp = string.split(' ')
	for i in (0..(temp.size)-1).step(2) do
		if(temp[i] != temp[i+1])
			if(hash.has_key?(temp[i]))
				hash[temp[i]] << temp[i+1].to_i
			else
				arr = Array.new
				arr << temp[i+1].to_i
				hash[temp[i]] = arr
			end
		end
	end
	return hash
end

def format_roots(string)
	return string.split(' ').each {|i| i.to_i}
end

def root_protect(root)
	temp = $objects[root]
	$objects.delete(root)
	$protected << root
	if("#{temp.class}" == "NilClass") or ($visited.include?(root)) #or ($protected.include? root)
		return
	else
		$visited << root
		temp.each do |i|
			puts i
			root_protect("#{i}")
		end
	end
end

def post(root)
	puts root
	temp = $objects[root]
	$objects.delete(root)
	if("#{temp.class}" == "NilClass") or ($protected.include? root)
		return
	else
		object_clean("#{root}")
		temp.each do |i|
			post("#{i}")
		end
	end	
end

def post_mul(root, result)
	temp = $objects[root]
	$objects.delete(root)
	if("#{temp.class}" == "NilClass") or ($protected.include? root) or ($visited.include?(root))
		return
	else
		result << "#{root} "
		post_mul("#{temp[0]}", result)
	end
	return result
end

def object_clean(object)
	uri = URI("http://#{ARGV[1]}:8080/api/sector/#{ARGV[0]}/company/vbgf/trajectory")
	res = Net::HTTP.post_form(uri, "trajectory" => "#{object}")
end

$roots = Net::HTTP.get(URI.parse("http://#{ARGV[1]}:8080/api/sector/#{ARGV[0]}/roots"))
$objects = Net::HTTP.get(URI.parse("http://#{ARGV[1]}:8080/api/sector/#{ARGV[0]}/objects"))
$roots = format_roots($roots)
$objects = format_objects($objects)
$protected = Set.new
$visited = Set.new

$roots.each do |root|
	root_protect(root)
end


puts "Working on sector #{ARGV[0]}"
puts "Number of obj to be removed: "
puts $objects.count

while(!$objects.empty?) do
	$objects.each_key do |i|
		result = String.new
		puts post_mul(i, result)
		object_clean("#{result[0...-1]}")
	end
end

puts "Done!"

#Old implementation with arrays,
#the new one executes a hash for faster seek times
#def format_objects(string)
#	pair = Array.new(2, 0)
#	arr = Array.new(0, pair)
#	temp = string.split(' ')
#	for i in (0..(temp.size)-1).step(2) do
#		pair[0] = temp[i]
#		pair[1] = temp[i+1]
#		arr[i/2] = pair[0..1]
#	end
#	return arr
#end

#def arr_to_hash (array)
#	arr = array.to_s.split(' ')
#	hash = Hash.new
#	for i in (0..(arr.size)-1).step(2) do
#		hash[arr[i]] = arr[i+1]
#	end
#	return hash
#end

#hashes = Array.new
#for i in 0..10 do
#	hashes[i] = arr_to_hash(objects[i])
#end
#puts hash[3]

# Will print response.body
#Net::HTTP.get_print(objects[2])
#puts objects[2]

#uri = URI("http://192.168.0.114:8080/api/sector/5/company/vbgf/trajectory")
#res = Net::HTTP.post_form(uri, "trajectory" => "8")
#puts res.body
