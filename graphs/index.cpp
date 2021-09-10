#include "index.h"
#include "../disks/index.h"
#include "../env/index.h"
#include "../utils/tools/index.h"
#include "string"

graph_commands::graph_commands() {}

/**
 * Reportes
 * @brief Generar reportes de todo tipo
 * @param props
 */
void graph_commands::rep(RepProps props) {
  string name = props.name;
  std::for_each(name.begin(), name.end(), [](char &c) { c = ::toupper(c); });

  // BUSCAR DISCO Y PARTICION
  MountedPartition partition;
  for (int m_index = 0; m_index < mounted_partitions.size(); m_index++) {
    if (mounted_partitions.at(m_index).id == props.id) {
      partition = mounted_partitions.at(m_index);
    }
  }

  if (name == "mbr") {
    disk_commands *disk_cmd = new disk_commands();
    disk_cmd->get_disk_graph(partition.path, props.path);
  } else {
    print_err("REP_ERR", "No existe esta opcion disponible para el reporte.")
  }
}