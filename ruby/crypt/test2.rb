require 'rsa'
data = "THIS IS SONE asldfknetogi "

key_pair = RSA::KeyPair.generate(64)
data.scan(/./).each do |char|
	ciphertext = key_pair.encrypt(char.ord)
	puts ciphertext
end

#text = key_pair.decrypt(ciphertext).chr

#puts ciphertext
#puts text
