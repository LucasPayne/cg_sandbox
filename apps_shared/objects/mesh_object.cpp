
Entity create_mesh_object(World &world,
                          const std::string &model_path,
                          const std::string &mat_path)
{
    Entity e = world.entities.add();
    auto t = e.add<Transform>();
    t->init(0,0,0);
    Resource<VertexArray> model = world.assets.models.load(model_path);

    Resource<GeometricMaterial> gmat = world.assets.shading.geometric_materials.load("resources/triangle_mesh.gmat");
    Resource<Material> mat = world.assets.shading.materials.load(mat_path);

    auto gmat_instance = GeometricMaterialInstance(gmat, model);
    auto mat_instance = MaterialInstance(mat);
    auto drawable = e.add<Drawable>(gmat_instance, mat_instance);
    return e;
}


