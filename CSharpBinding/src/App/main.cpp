#include <iostream>
#include <mono\jit\jit.h>
#include <mono\metadata\assembly.h>

int main(void)
{
  MonoDomain *monoDomain = mono_jit_init_version("embedding_mono_domain",
                                                 "v4.0.30319");

  MonoAssembly *assembly = mono_domain_assembly_open(monoDomain, "Example.dll");

  MonoImage *monoImage = mono_assembly_get_image(assembly);

  MonoClass *entityClass = mono_class_from_name(monoImage, "Example", "Entity");

  MonoObject *entityInstance = mono_object_new(monoDomain, entityClass);

  MonoMethod *constructorMethod = mono_class_get_method_from_name(entityClass, ".ctor", 1);
  
  MonoString *name = mono_string_new(mono_domain_get(), "Giorgos");
  void *args[1];
  args[0] = name;

  MonoObject *exception = NULL;
  mono_runtime_invoke(constructorMethod, entityInstance, args, &exception);

  MonoMethod *processMethod = mono_class_get_method_from_name(entityClass, "Process", 0);
  exception = nullptr;

  mono_runtime_invoke(processMethod, entityInstance, nullptr, &exception);

  if (exception)
  {
    std::cout << mono_string_to_utf8(mono_object_to_string(exception, nullptr)) << std::endl;
  }

  MonoMethod *getNameMethod = mono_class_get_method_from_name(entityClass, "GetName", 0);

  exception = nullptr;
  MonoString *ret = (MonoString *)mono_runtime_invoke(getNameMethod, entityInstance, nullptr, &exception);
  char *c = mono_string_to_utf8(ret);
  std::cout << "Value of 'name' is " << c << std::endl;

  MonoClassField *idField = mono_class_get_field_from_name(entityClass, "Id");
  int value = 42;

  mono_field_set_value(entityInstance, idField, &value);

  int result;
  mono_field_get_value(entityInstance, idField, &result);
  std::cout << "Value of 'Id' is " << result << std::endl;

  mono_jit_cleanup(monoDomain);

  return 0;
}