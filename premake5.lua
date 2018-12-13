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
--    '/usr/local/Arnl/include',
    'include'
}

libdirs {
    '/usr/local/Aria/lib',
--    '/usr/local/Arnl/lib'
}

links {
    'Aria',
    'ArNetworking',
--    'BaseArnl',
--    'Arnl',
--    'SonArnl',
--    'ArNetworkingForArnl',
--    'AriaForArnl'
}

files {
    'src/ActionExploreVelocity.cpp',
    'src/ActionExploreAvoid.cpp',
    'src/NavBot.cpp'
}
