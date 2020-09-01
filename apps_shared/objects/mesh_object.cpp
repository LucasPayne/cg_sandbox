
Entity create_mesh_object(World &world,
                          const std::string &model_path,
                          const std::string &mat_path)
{
    Entity e = world.entities.add();
    auto t = e.add<Transform>();
    t->init(0,0,0);
    Resource<VertexArray> model = world.assets.models.load(model_path);

    Resource<GeometricMaterial> gmat = world.assets.shading.load_geometric_material("resources/triangle_mesh.gmat");
    Resource<Material> mat = world.assets.shading.load_material(mat_path);
    auto drawable = e.add<Drawable>(GeometricMaterialInstance(gmat, model),
				    MaterialInstance(mat));

    return e;
}

