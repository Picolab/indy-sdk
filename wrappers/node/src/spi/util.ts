import { ErrorCode, IndyError } from '../error'
import {
  JSON_Datum,
  FilesystemPath,
} from '../bridge'
import {
  DID,
  A_DID_Utils,
  A_DID_and_Me,
  Target,
  Ledger,
  SubmitterTools,
  Wallet,
  LedgerGenesisTransaction,
  IP_Port,
  IP_Addr,
  TXN_DEST,
  TXN_IDENTIFIER,
  TXN_ID,
  TXN_Type
} from '../spi'

export class C_LedgerGenesisTransaction implements LedgerGenesisTransaction {

  readonly alias : string
  readonly client_ip : IP_Addr
  readonly client_port: IP_Port
  readonly node_ip:IP_Addr
  readonly node_port: IP_Port
  readonly services:string[]
  readonly dest:TXN_DEST
  readonly identifier:TXN_IDENTIFIER
  readonly txnId:TXN_ID
  readonly type:TXN_Type

  as_wrapped_json_string() : string {
    return JSON.stringify({ data:this })
  }

  constructor(payload:any) {
    let bolus = payload.data
    if(bolus === undefined)
      bolus = payload
    this.alias = bolus.alias
    this.client_ip = bolus.client_ip
    this.client_port = bolus.client_port
    this.node_ip = bolus.node_ip
    this.node_port = bolus.node_port
    this.services = bolus.services || ["VALIDATOR"]
    this.dest = bolus.dest
    this.identifier = bolus.identifier
    this.txnId = bolus.txnId
    this.type = bolus.type || "0"
  }

}


export class C_Target implements Target {
  readonly builder:SubmitterTools
  readonly target:DID

  constructor(builder:SubmitterTools,target:DID) {
    this.builder = builder
    this.target = target
  }

  async node_request( data:string ) : Promise<void> {
  }

  async get_ddo_request() : Promise<void> {
  }

  async nym_request(verkey:string, alias:string, role:string ) : Promise<void> {
  }
  async get_nym_request( ) : Promise<void> {
  }

  async attrib_request(hash:string, raw:string,  enc:string ) : Promise<void> {
  }
  async get_attrib_request(data:string ) : Promise<void> {
  }

}

export class C_SubmitterTools implements SubmitterTools {

  readonly submitter:DID
  readonly ledger:Ledger

  constructor(ledger:Ledger,submitter:DID) {
    this.submitter = submitter
    this.ledger = ledger
  }

  target(target:DID) : Target {
    return new C_Target(this,target)
  }

  async schema_request(data:string ) : Promise<void> {
  }

  async get_schema_request(dest:string, data:string ) : Promise<void> {
  }

  async claim_def_txn( xref:number,  signature_type:string,  data:string ) : Promise<void> {
  }

  async get_claim_def_txn( xref:number,  signature_type:string,  origin:string ) : Promise<void> {
  }

  async get_txn_request(data:number ) : Promise<void> {
  }

}



export class C_A_DID_and_Me implements A_DID_and_Me {
  readonly a_did:DID
  readonly me:DID
  constructor(a_did:DID,me:DID) {
    this.a_did = a_did
    this.me = me
  }

  encrypt(pool_ledger:Ledger, message_raw:Buffer) {
  }

  decrypt(encrypted_msg_raw:Buffer, nonce_raw:Buffer) {
  }
}


export class C_A_DID_Utils implements A_DID_Utils {
  readonly a_did:DID

  replace_keys(identity_json:string) {
  }

  sign(message_raw:Buffer) {
  }

  verify_signature(pool_ledger:Ledger, message_raw:Buffer, signature_raw:Buffer) {
  }

  and_me(me:DID) : A_DID_and_Me {
    return new C_A_DID_and_Me(this.a_did,me)
  }
}
