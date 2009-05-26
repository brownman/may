PROJECT(may)

link_libraries(GL GLU X11 Xext Xxf86vm Irrlicht BulletCollision BulletDynamics LinearMath)

ADD_EXECUTABLE(may 
				main.cpp 
				src/support/cd_wavefront.cpp 
				src/support/float_math.cpp
				src/Physics.cpp
				src/Entity.cpp
				src/EntityManager.cpp
				src/GraphicsEngine.cpp
				)

