--[=====[ 

testString = "LuaBridge works!"
number = 42

window = {
    title = "Window v.0.1",
    width = 400,
    height = 500,
    sumNumbers = function(a,b)
        printMessage("You can still call C++ functions from Lua functions!")
        return a + b
    end
}

printMessage("You can call C++ functions from Lua!")

--]=====]

script = {
    GraphicsComponent = {
        filename = "TheFileName",
        size = {
            width = 666,
            height = 666
        }
    },
    NpcComponent = {
        name = "The Cika Protos",
        sub_name = "Senior protos",
        on_interact = function()
            print "TheIntersectFunctionInNpc"
        end
    }

}