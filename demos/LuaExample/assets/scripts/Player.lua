Player = class("Player")

-- contructor of player
function Player:construct(fields)
    self.sprite = Sprite.load(fields.getString("sprite"))
    self.counter = 0
end

-- on update
function Player:update(delta)
    self.counter = self.counter + self.speed * delta
end

-- on fixed update
function Player:fixedUpdate(delta)
    -- none
end

-- on render 2D
function Player:render2D(renderer2D)
    local transform2D = self.getComponent(Transform2D)
    renderer2D.getLayer2D("bg").drawSprite(self.sprite, transform2D.global())
end

-- on input
function Player:inputEvent(event)
    --
end
