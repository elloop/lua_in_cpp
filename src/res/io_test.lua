-- simple io, read, write, 
-- integrate io module. io.input, io.output, io.open()

local fnames = {
    "print", -- write to stdin.
    "write", -- write to file.
    "read", -- read from file, *all, *line, *number, <n>
}

local simpleIO = {}

function simpleIO:test()
    -- self:print()
    self:read()
    -- self:write()
end

function simpleIO:read()
    -- *number
    -- local n = io.read("*number")
    -- if tonumber(n) then
        -- print("el## n: " .. n)
    -- else
        -- print("el## n is not a number")
    -- end

    -- *line
    -- local str = io.read("*line")
    -- print(str)

    -- *all
    -- local all = io.read("*all")
    -- print(all)

    -- <n> chars
    local some = io.read(2^3) -- read 8 chars from stdin. 
    print(some)
end

function simpleIO:write()
    local a, b, c = 10, 20, 30
    -- print("el## a, b, c" .. ": " .. a .. ", " .. b .. ", ".. c) -- stdout , call tostring.

    io.write("a, b, c: ", a, " ", b, " ", c)
    -- io.write("a" .. a .. "b" .. b .. "c" .. c) -- do not do this. 
end

----------------------------------integerate module ------------------------------------

local completeIO = {}

local cfname = {
    "open", -- like fopen in C. 
}

function completeIO:test()
    -- self:open()
    -- self:predefinedHandle()
    -- self:switchHandle()
    self:fastReadBigFile()
    -- self:createBigFile()
end

-- io.open and read.
function completeIO:open()
    local files = {
        {
            name = "/etc/passwd",
            mode = "w"
        }, -- nil Permission denied  13

        {
            name = "io_test1.lua",
            mode = "r"
        }, -- nil No such file or directory  2 

        {
            name = "main.lua",
            mode = "r",
        }, -- ok 
    }

    for i,v in ipairs(files) do
        print(io.open(v.name, v.mode))
    end

    local f = assert(io.open("main.lua", "r"))
    local lines = f:read("*all")
    -- local lines = io.read("*all") -- this is still reading from stdin 
    print("el## lines: " .. lines)
    f:close()
end

-- predefined io file handle: stdin, stdout, stderr
function completeIO:predefinedHandle()
    io.stdout:write("input a number:")
    local n = io.stdin:read("*number")
    io.stdout:write("number into stdout: : ", n, "\n")
    io.stderr:write("number into stderr: ", n, "\n")
end

-- api to modify current file handle: io.input() or io.input(newHandle)
function completeIO:switchHandle()

    -- get current input handle.
    local oldHandle = io.input() 
    assert(oldHandle == io.stdin) -- oldHandle == io.stdin 

    -- switch io file handle useing io.input 
    local f = assert(io.open("main.lua", "r"))
    io.input(f) -- swith to new input handle 
    local line = io.read("*line")
    print("el## line: " .. line)

    io.input(oldHandle) -- switch back to stdin 
    local line2 = io.read("*line")
    print("el## line2: " .. line2)

    -- the same situation in io.output()
    local oldOutHandle = io.output()
    assert(oldOutHandle == io.stdout)

    local outf = assert(io.open("temp.lua", "w"))
    io.output(outf) -- switch to another output file handle.
    io.write("require 'test/t'", "\n", "local str = 'write into here instead of stdout'")

    io.output(oldOutHandle)
    io.write("back into stdout")
end

function completeIO:fastReadBigFile()
    -- the big_file is 33M. 
    
    local t1 = os.time()
    local fileName = "big_file"
    local f = assert(io.open(fileName, "r"))
    -- local allLines = f:read("*all") -- this will be impossible if the file is very big.
    -- we should read by block when we meet big files.
    local BLOCK_SIZE = 2^18 -- 32K 
    local allLines = ""
    local count = 0
    while true do
        local content, rest = f:read(BLOCK_SIZE, "*line")
        if not content then
            break
        end

        if rest then
            content = content .. rest .. "\n"
        end

        -- count = count + 1
        -- if count % 50 == 0  then
            -- print("el## count: " .. count)
            -- print("el## content:   " .. content)
        -- end

        -- now content is a whole block with the entire line. 
        allLines = allLines .. content -- we don't sugguset use concat this way.
    end
    -- now allLines will be the whole content of the file.
    -- print("el## allLines: " .. allLines)

    local t2 = os.time()

    print("el## t2 - t1: " .. (t2 - t1))

    -- now we create a very big file. 
end

function completeIO:createBigFile()
    -- create a big string file, with line nubmer very line, so that we will be easy to read the output of the reading content.
    local fileName = "big_file"
    local lines = 2^20 -- 1M lines 
    local f = assert(io.open(fileName, "w"))
    for i=1, lines do
        f:write(i, "---line contents is ignore", "\n")
    end
    f:close()
end

local dumpHex = function(filename)
    local f = assert(io.open(filename, "rb"))
    local block = 16
    while true do
        local bytes = f:read(block)
        if not bytes then
            break
        end
        for _,b in ipairs{string.byte(bytes, 1, -1)} do
            io.write(string.format("%02X ", b))
        end
        io.write(string.rep("   ", block - string.len(bytes)))
        io.write(" ", string.gsub(bytes, "%c", "."), "\n")
    end
    f:close()
end

-- simpleIO:test()
-- completeIO:test()

dumpHex("main.lua")


