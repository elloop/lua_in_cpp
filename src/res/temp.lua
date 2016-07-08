require 'test/t'
local str = 'write into here instead of stdout'

function testLen()
    local s = "hello" -- 5 chars 
    local sbytes = string.char(97, 98, 0, 0, 0)
    print("el## sbytes: " .. sbytes) -- ab

    print("el## strlen(sbytes): " .. string.len(sbytes)) -- len is 5, not 3!!! 
    print("el## strlen(s): " .. string.len(s))
end

testLen()
