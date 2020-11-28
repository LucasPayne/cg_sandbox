
Entity create_mesh_object(World &world,
                          MLModel &model,
                          const std::string &mat_path)
{
    if (!model.has_normals) model.compute_phong_normals();

    Entity e = world.entities.add();
    auto t = e.add<Transform>(0,0,0);
    auto box = BoundingBox(model.positions);
    auto sphere = box.bounding_sphere();
    
    Resource<GeometricMaterial> gmat = world.graphics.shading.geometric_materials.load("shaders/triangle_mesh/triangle_mesh.gmat");
    Resource<Material> mat = world.graphics.shading.materials.load(mat_path);

    VertexArrayData vad;
    MLModel_to_VertexArrayData(model, vad);

    auto va = world.resources.add<VertexArray>();
    *va = VertexArray::from_vertex_array_data(vad);

    // Resource<VertexArray> model_vertex_array = world.assets.models.load(model_path);
    auto gmat_instance = GeometricMaterialInstance(gmat, va);
    auto mat_instance = MaterialInstance(mat);
    auto drawable = e.add<Drawable>(gmat_instance, mat_instance);
    drawable->raw_bounding_sphere = sphere;
    return e;
}

Entity create_mesh_object(World &world,
                          const std::string &model_path,
                          const std::string &mat_path)
{
    auto model = MLModel::load(model_path);
    return create_mesh_object(world, model, mat_path);
}


