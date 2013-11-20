#!/usr/bin/ruby

Dir.new('.').each { |item|
    if (item[-2..-1] == '.h')
        f = File.new(item[0..-3], 'w')
        f.write("#include \"#{item}\"\n\n")
        f.close()
    end
}
