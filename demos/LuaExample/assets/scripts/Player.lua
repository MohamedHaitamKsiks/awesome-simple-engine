Player = Component("Player", {
    sprite = nil,
    counter = 0
})

-- export fields for serialiazation
-- this will be added after the serialiazation update
Player.export(
    {"sprite", "Sprite"},
    {"counter", "Int"}
);

-- on update
function Player:on_create(entityID)
    -- pass
end

-- on fixed update
function Player:on_destroy()
    -- pass
end
