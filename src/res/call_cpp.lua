package.cpath = package.cpath .. ";../lib/?.so"

require "ellua"         -- dynamic load libellua.so under ../lib/ 

local x = ellua.listdir(".")

print("ret type of ellua.listdir(): " .. type(x))

if type(x) == "table" then
    for k,v in pairs(x) do
        print("k, v = " .. tostring(k) .. ", " .. tostring(v))
    end
end

