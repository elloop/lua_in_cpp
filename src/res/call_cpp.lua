package.cpath = package.cpath .. ":../../lib/"
require "ellibs"

local x = ellibs.listdir(".")

print(type(x))

if type(x) == "table" then
    for k,v in pairs(x) do
        print("k, v = " .. tostring(k) .. ", " .. tostring(v))
    end
end

