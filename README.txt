Para ejecutar hay que modificar en las propiedades el VulkanSDK (requisito tener VulkanSDK descargado):
En mi caso lo tengo en el directorio C

1. Proyecto -> Propiedades
2. C/C++ -> General -> Directorio de inclusión adicionales
3. Añadir C:\VulkanSDK\<version>\Include
4. Vinculador -> General -> Directorios de bibliotecas adicionales
5. Añadir C:\VulkanSDK\<version>\Lib
