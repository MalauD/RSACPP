# CMakeList.txt : projet CMake pour RSACpp, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)
project(RSACpp VERSION 0.1.0)


file(GLOB_RECURSE SRCs "./src/*")
# Ajoutez une source à l'exécutable de ce projet.
add_executable (RSACpp ${SRCs})

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
