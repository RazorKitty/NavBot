workspace 'NavBot'
configurations {'Release'}

project 'NavBot'
--architecture 'x86_64'
language 'c++'
kind 'ConsoleApp'

includedirs {
    '/usr/local/Aria/include',
    '/usr/local/Aria/ArNetworking/include',
}

libdirs {
    '/usr/local/Aria/lib',
}

links {
    'Aria',
    'ArNetworking',
}

files {
    'NavBotUtil.cpp',
    'ActionExploreVelocity.cpp',
    'ActionExploreAvoidFrontNear.cpp',
    'ActionExploreNavigateNear.cpp',
    'SensorSweepTask.cpp',
    'LineExtractionTask.cpp',
    'NavBot.cpp'
}
