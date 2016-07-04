local fnames = {
    "print", -- write to stdin.
    "write", -- write to file.
    "read", -- read from file, *all, *line, *number
}

local ioTest = {}

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
    -- self:read()
    self:write()
end

function ioTest:read()
    local n = io.read("*number")
    if tonumber(n) then
        print("el## n: " .. n)
    else
        print("el## n is not a number")
    end

    local str = io.read("*line")
    print(str)
end

function ioTest:write()
    local a, b, c = 10, 20, 30
    print("el## a, b, c" .. ": " .. a .. ", " .. b .. ", ".. c)
    io.write("a, b, c: ", a, " ", b, " ", c)
    -- do not use .. to concat string in write because of effeciency.
    -- print will call __tostring automatically, but write won't 
end

ioTest.test(ioTest)


