require 'rsa'
data = "THIS IS SOME SECURE SHIZ"

key_pair = RSA::KeyPair.generate(64)

def encrypt(key_pair, data)
	ans = []
	data.scan(/./).each do |char|
		ciphertext = key_pair.encrypt(char)
		ans << ciphertext
	end
	return ans
end

def decrypt(key_pair, data)
	ans = ""
	data.each do |ciphertext|
		text = key_pair.decrypt(ciphertext)
		ans << text
	end
	return ans
end

crypt = encrypt(key_pair, data)
puts crypt
text = decrypt(key_pair, crypt)
puts text

puts key_pair.private_key.exponent
puts key_pair.public_key.modulus
