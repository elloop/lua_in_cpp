local fname = {
    "find",   -- return [i, j]
    "rep",    -- rep n times to create a string
    "sub",    -- return  sub string
    "match",  -- return string
    "gsub",   -- return new string substitued, global substitution.
    "gmatch", -- return a function for iteration, global match
}

-- all done. begin new test for io.

local strtest = {}

function strtest.rep()
    local s = string.rep("c", 10)
    print("el## s: " .. s) -- 10 c 

    local s1 = string.rep("hello", 3)
    print("el## s1: " .. s1)

    local s2 = string.rep("x", 2^10)
    print("el## s2: " .. s2) -- you see 1024 x. 

    local verylong = string.rep("0", 2^20)
    print("el## verylong: " .. verylong) -- you see 1M chars. 
end

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
    local t = {string.byte(s, 1, -1)}
    print("el## type(t)" .. type(t))
    print(t)

    print("el## recover string: ")
    local sb = string.char(unpack(t))
    print(sb)

    local suffix2 = string.sub(s, -2)
    print("el## suffix2: " .. suffix2)

    local prefix2 = string.sub(s, 1, 2)
    print("el## prefix2: " .. prefix2)
end

function strtest.match()
    local s = "my birth day is 1988-06-12."

    local basic = string.match(s, "day")
    print("el## basic: " .. basic)

    local advance = string.match(s, "%d+-%d+-%d+")
    print(advance)
end

function strtest.gsub()
    -- simple sub. 
    local s = "tom is a dog, dog eat mouse"
    local se = string.gsub(s, "dog", "cat")
    print("el## se: " .. se)

    -- sub base on pattern 
    local myInfo = "my age is 18, my height is 180"
    local secret = string.gsub(myInfo, "%d+", "unknown")
    print("el## secret: " .. secret)

    -- other advanced usage. see PIL chapter 20. 
end

function strtest.gmatch()
    local s = "10 X 10 == 100"
    local numberTable = {}
    for num in string.gmatch(s, "%d+") do
        numberTable[#numberTable + 1] = num
    end
    setmetatable(numberTable, {
        __tostring = function()
            -- todo: how to implement a tostring function for table. 
            return "hello world"
        end
    })
    print(numberTable) -- hello world 
    for index,v in ipairs(numberTable) do
        print("el## index, v: " .. index .. ", " .. v)
    end
end

function strtest.tests()
    -- strtest.find()
    -- strtest.match()
    -- strtest.sub()
    -- strtest.rep()
    -- strtest.gsub()
    strtest.gmatch()
end

strtest.tests()

