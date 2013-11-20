#!/usr/bin/ruby

require 'fileutils'

SrcDir = '../src'
DstDir = '../include/QtWui'
@@identifiers = { "QwuiGlobal" => File.join(SrcDir, "kernel/qwuiglobal.h") }

def printUsage()
    puts "Scans all header files of <source dir> and generates the corresponding"
    puts "distribution include files in <destination dir>"
    puts
    puts "Usage:"
    puts "         create-include-files.rb [options] <source dir> <destination dir>"
    puts "Options:"
    puts "         -r    scan recursively source directory"
end

def addDirIdentifiers(ids, dir)
    puts "Scanning #{dir} ..."
    ctags = IO.popen("ctags --c-types=gtc --fields=k -f - #{File.join(dir, '*.h')}")
    ctags.each { |line|
        items = line.split(/\s/)
        if (items.length > 1) then
            # Filter class internal enums
            if (items[0][0, 4] == "Qwui") then
                ids[items[0]] = items[1]
            end
        end
    }
    return ids
end

def scanSourceDir()
    ids = Hash.new
    Dir.foreach(SrcDir) { |item|
        if (item[0, 1] != '.') then
            itemPath = File.join(SrcDir, item)
            if (File.stat(itemPath).directory?) then
                addDirIdentifiers(ids, itemPath)
            end
        end
    }
    return ids
end

def createIncludeFiles()
    FileUtils.remove_dir(DstDir, true)
    FileUtils.makedirs(DstDir)
    ids = scanSourceDir()
    @@identifiers.each { |identifier, filename|
        ids[identifier] = filename
    }
    ids.each { |identifier, filename|
        incFilename = File.join(DstDir, identifier)
        file = File.new(incFilename, 'w')
        file.write('#include "' + File.join('..', filename) + "\"\n")
        incFilename = File.join(DstDir, identifier.downcase + '.h')
        file = File.new(incFilename, 'w')
        file.write('#include "' + File.join('..', filename) + "\"\n")
    }
end

createIncludeFiles()
