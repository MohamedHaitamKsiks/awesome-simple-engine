#include "LuaScriptManager.h"

namespace ASEngine
{
// script manager is fully in the lua side
static constexpr char s_LuaScript[] = R"lua(
-- basic script type
Script = {}
function Script:new(entityID)
    local obj = {}
    obj.entityID = entityID
    setmetatable(obj, {__index = Script})
    return obj
end

function Script:create()
end

function Script:update(delta)
end

function Script:fixedUpdate(delta)
end

function Script:render2D()
end

function Script:destroy()
end

-- manager of the different scripts attached to the each entity --
-- should not be used by the user --
ScriptManager = {}
ScriptManager.entities = {}
ScriptManager.scriptClasses = {}

-- create instance of a script by it's class name --
function ScriptInstanceCreate(className, entityID, fields)
    local scriptType = ScriptManager.scriptClasses[className]

    local obj = scriptType:new(entityID)

    if (ScriptManager.entities[entityID]) then
        ScriptManager.entities[entityID] = {}
    end

    table.insert(ScriptManager.entities, obj)
    return obj
end

-- update all scripts
function Update(delta)
    for entityID, scripts in pairs(ScriptManager.entities) do
        for k, script in pairs(scripts) do
            script:update(delta)
        end
    end
end

--- create new class with a name
function Class(className)
    local scriptClass = {}

    scriptClass.new = function (entityID)
        local obj = Script:new(entityID)
        setmetatable(obj, {__index = scriptClass})
        obj:construct()
        return obj
    end

    scriptClass.className = function ()
        return className
    end
base
    ScriptManager.scriptClasses[className] = scriptClass

    return scriptClass
end

)lua";

    void LuaScriptManager::Init()
    {
    }

} // ASEngine
