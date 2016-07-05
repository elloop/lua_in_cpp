-- simple io, read, write, 
-- integrate io module. io.input, io.output, io.open()

local fnames = {
    "print", -- write to stdin.
    "write", -- write to file.
    "read", -- read from file, *all, *line, *number, <n>
}

local ioTest = {}

-- stdin
-- stdout

function ioTest:print()
    local t = {
        "hello",
        "this is a table"
    }
    print(t)

    local mt = {}
    mt.__tostring = function(k)
        return tostring(t[k])
    end
    setmetatable(t, mt)
    print(t)
end

function ioTest:test()
    -- self:print()
    self:read()
    -- self:write()
end

function ioTest:read()
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

function ioTest:write()
    local a, b, c = 10, 20, 30
    -- print("el## a, b, c" .. ": " .. a .. ", " .. b .. ", ".. c) -- stdout , __tostring

    io.write("a, b, c: ", a, " ", b, " ", c)

    -- io.write("a" .. a .. "b" .. b .. "c" .. c) -- do not do this. 
  
    -- do not use .. to concat string in write because of effeciency.
    -- print will call __tostring automatically, but write won't 
end

ioTest.test(ioTest)


