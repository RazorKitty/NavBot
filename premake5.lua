workspace 'NavBot'
configurations {'Release'}

project 'NavBot'
architecture 'x86_64'
language 'c++'
kind 'ConsoleApp'
--[[
includedirs {
    '/usr/local/Aria/include',
    '/usr/local/Aria/ArNetworking/include',
    '/usr/local/Arnl/include',
    'include'
}

libdirs {
    '/usr/local/Aria/lib',
    '/usr/local/Arnl/lib'
}
--]]

includedirs {
    '/usr/local/Aria/include',
    '/usr/local/Aria/ArNetworking/include',
    'include'
}

libdirs {
    '/usr/local/Aria/lib',
}

links {
    'Aria',
    'ArNetworking',
}

files {
    'src/NavBotUtil.cpp',
    'src/ActionExploreVelocity.cpp',
    'src/ActionExploreAvoidFrontNear.cpp',
    'src/ActionExploreNavigateNear.cpp',
    'src/SensorInterpretTaskContainer.cpp',
    'src/NavBot.cpp'
}
