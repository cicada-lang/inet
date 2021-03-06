import { Edge } from "../edge"
import { Node } from "../node"
import { Type } from "../type"

export class Port {
  node: Node
  index: number
  t: Type
  connection?: {
    edge: Edge
    port: Port
  }

  constructor(node: Node, index: number) {
    this.node = node
    this.index = index
    this.t = node.types[index]
  }

  format(): string {
    return `${this.node.format()}(${this.index})`
  }

  inspect(): any {
    return {
      node: this.node.format(),
      index: this.index,
      t: this.t.format(),
    }
  }

  isPrincipal(): boolean {
    return this.t.isPrincipal()
  }
}
