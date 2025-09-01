PlayerSystem = System("PlayerSystem")

function PlayerSystem:update(delta)
    local query = EntityQuery.new("Transform2D", "Player");
    
    query:forEach(
        function (transform2D, player)
            transform2D.position = transform2D.position + player.velocity * delta
        end
    );
end
