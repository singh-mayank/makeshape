#----------------------------------------------------------------------
# makeshape
#----------------------------------------------------------------------

add_subdirectory(common)
add_subdirectory(spatial)
# goes into spatial
#add_subdirectory(dual_contouring)
# these go into surface 
# add_subdirectory(poisson_surf_recon)
# add_subdirectory(wavelets_surf_recon)
# this needs renderables
# add_subdirectory(shapes)

add_subdirectory(app)
