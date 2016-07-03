local fname = {
    "find",   -- return [i, j]
    "sub",    -- return  sub string
    "match",  -- return string
    "gsub",   -- return new string substitued
    "gmatch", -- return a function for iteration
}

local strtest = {}

function strtest.find()
    local s = "1988-06-12"
    print(string.find(s, "06"))
    print(s:find("06")) -- since lua 5.1 
end

function strtest.sub()
    local s = "[he is a substring of hello]"
    print("el## original string: " .. s)
    print("el## original string [2, -2]")
    print(string.sub(s, 2, -2))

    print("el## save string into a byte array: ")
    local t = string.byte(s, 1, -1)
    print(t)

    print("el## recover string: ")
    local sb = string.char(unpack(t))
    print(sb)
end

function strtest.match()
    local s = "my birth day is 1988-06-12."
    local ret = string.match(s, "%d+-%d+-%d+")
    print(ret)
end

function strtest.tests()
    -- strtest.find()
    -- strtest.match()
    strtest.sub()
end
strtest.tests()
