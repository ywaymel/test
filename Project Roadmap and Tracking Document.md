---
project: pjneko
version: Working Draft 0.4.21a
authors:
 - Perle <lpinf@scpija.com>
working groups:
  - Scpija Labs Core
status:
  - private
access level: 1
tags:
  - scpija
  - pjneko
  - track_doc
---
# Project Evolution Tracker

> [!info] Working Draft 0.4.21a
> *Project:* pjneko (PET)
> *Status:* private (level 1)
> *Working group:* Scpija Labs Core
> *Authored by:* Perle \<lpinf@scpija.com>

**PET is a personal and professional organization/planning aggregator and provider.** At its core, it is a graph engine and a routing engine that can be viewed using views on a client. It also lets user store their identity anywhere, even locally.

To a *user* of the application, PET is an organization tool that seamlessly connects with all of their tools, and that can be personalized to their needs.
To an *organization*, PET allows its members to stay in touch with their work, while letting them know of their availability, making it handy for quick, frictionless communication and task distribution.
To a *corporation with existing infrastructure*, PET can seamlessly integrate with existing SSO and tooling without sudden replacements, making its implementation cost relatively low.

PET also aims to be an **accessible platform for everyone**, with customizable theming, robust accessibility standards for visually impaired people, and most importantly significant adaptability capabilities, meaning it can adapt to each and every person's individual needs (for example, reducing the field of view for people with ADHD or relieving anxious people from having to choose what to do next.)

# Visual Structure

PET is structured around a more general "space" theme. This lets users give names to the complicated abstractions going on behind the scenes, rather than saying "the graph thing" or "the organization thing", they can say "the organization planet" or "my project on my homeplanet".

## Planets and homeplanets

PET is split up into **"planets" (top-level containers)** which act as top-level groups for organizations, which then can contain sub-groups, integrations, or projects.

There is **one homeplanet per user**, which can contain personal projects, integrations and groups not meant to be shared. Users may create planets on a server when they want projects, integration and groups meant to be shared. Planets are intended to be hosted on a server directly, but a server can host multiple planets.

Homeplanets **can be stored on the client or on a homeserver** (a server you, as a user, trust to handle your information, or host yourself), with the only difference being convenience related to data and key syncing across multiple clients. By contrast, local-only homeplanets can only sync over local networks.

> [!tip]
> In *workflows* (see *Automation module*), homeplanets expose a unique `homeplanet-flow` API (also known as *observatory API*) which allows searching across all planets and satellites this user account knows.

An integration can also take the form of a planet, such as a github organization: this is known as a lone Satellite. You can also add integrations within a planet, which is also known as an Orbiting Satellite (for more details, see the *Satellites* section).

## Projects

Projects, within planets, are a large graph structure that allows them to contain pretty much any kind of data. From tasks, to calendar events, to files and folders, to workflows and canvases. These graph structures are also contained by planets in a less "explicit" way, as it is mainly used as a container for properties. These graphs can be linked to other graphs across different planets using remote links in `pet://`.

For more information about the graph and its node types, see the *Graph* section and the *Planned node types and views* section below.

# Practical Structure

PET is a complex, client-heavy application made of multiple components. This practically means most of the processing happens locally on the client, while the server mainly acts as authentication, storage and validation, as well as the main provider for synchronization (CRDTs host) and permission access control. This peculiar choice was made as the application is designed to run both entirely on the client or connected to a homeserver or organization server.

The application is divided into multiple main groups, each divided into components.

- **Client**: components that are part of the client.
	- **Graph Node Views**: views over the graph nodes, like global views (such as kandan) or node views (like view over a task)
	- **Local Storage / Cache**: When using a homeserver, the client maintains a cache to avoid intense fetching, but without a homeserver, the client stores everything directly (both methods use IndexedDB and service workers).
	
- **Shared**: components that are shared between client and server. They can be implemented twice, or share the same implementation across server and client.
	- **WKI**: Web Key Identities implementation based on OpenSSL (server) and SubtleCrypto (client)
	- **Graph Engine**: graph resolution engine (resolve links in `pet://`, perform tasks, etc.)
	
- **Server**: components that are part of a server.
	- **CRDT resolution**: The server is responsible for syncing the replicated data structures together.
	- **Validation and authorization**: Access-control on permissions, and validation of inbound request.
	- **Server-side Database**: relational DB, like PostgreSQL or Scpija VoxelDB (originally VoxelDB was meant to be its core platform, but the current version is on PostgreSQL while the VoxelDB team gets time to improve the project)

What actually runs on the server or on the client is mainly decided by what "owns" the current planet. For example, a planet stored on the client runs its scripts on the client, while a planet stored on a server runs its script from the server.

# Identity and WKI

WKI stands for **Web Key Identities**, the decentralized identity management system used for PET's authentication, encryption and user management.

## Identity

In WKI, an identity can be reduced to only **a user's public key**. In PET, there are multiple identity types:
- *Transient identities*, identities where the key is not trusted yet, and the user never logged in.
- *Minimal identities*: a user's public key, and that's it.
- *Complete identities*: a user's public key signed using their sudo key, accompanied with their username and profile information. This identity type automatically gets populated on first login to a new server.
## Keys

Similarly to SSH, the WKI system relies on keypairs. In WKI's case, it supports common SSH key types, but the main key type is **ed25519**. This key is handled through **OpenSSL on the server, and SubtleCrypto on the client**, and it is synchronized across all user devices.

Additionally, a second, derived and password-protected key is generated to act as the *sudo key*, a special key meant for first sign-in and key rotation. This key is never stored.
## Authentication

The WKI framework functions with various authentication modes. The primary authentication mode is **key-sign mode**, where every WKI request must be signed, as the signature itself provides authentication. Other authentication modes exist, such as **Personal Access Token mode, or just token mode**, which instead solely relies on a token stored securely on the server itself. Finally, the last authentication mode is **public mode**, which simply does not authenticate, and attempts to access the resource as a public resource, since some nodes or projects can be made public.

When linking nodes (See *Linking* section), you can use the `auth=` inline URL option which lets you select the authentication mode:
- `"key"` uses normal WKI signed authentication, and is the implied default
- `"token"` uses a defined Personal Access Token or Project Access Token for authentication
- `"public"` uses no authentication and simply attempts to get the resource
## Joining planets

In PET, a *server* is an actual, physical or virtual machine that receives the PET information, and it must have a domain name or an IP address. Joining a server is **done by joining one of the server's planets**, so if a server has no planets you can join, you can't join the server.

Planets **can be invite-only or public**, and the same goes for individual projects within the planet.
### Sharing your identity

To be invited or join a planet, you need to **share your public key** with the server. In short, either the planet asks you for your identity, or you need to provide it to the planet or the planet's admin. This behavior is configurable on a per-planet basis.

To share your identity to a third party, for example a planet admin that would like to invite you, there is a myriad of ways you can share your key, with varying levels of security enforcement:
- `@user:server.example` *(Homeserver ID)*: This user ID is one of the simplest, most readable, and most secure ways to join a planet. The planet's admin can enter this in their members tab, and your homeserver will be queried for the user's public key. This also lets them send an invite push notification if you have those enabled.
- `@user!fingerprint` *(Fingerprint ID)*: This user ID is the username accompanied with a public key fingerprint that's at least 8 hex digits. This is a simple method to invite users with no homeservers, although it can be bruteforced, so a warning displays for any key under 12 digits.
- `<@user!!fullkey>` *(Secure ID)*: This user ID embeds the full ed25519 public key (`<@user!!AAAA..>`). This method is less readable, but more secure than fingerprint ID to let users with no homeserver join your planet or project.
- `ssh-ed25519 AAAA... @user` *(SSH ID)*: Similar to *Secure ID*, this format embeds the full ed25519 key, this time in the standard SSH format. The only difference this has, is that this ID will not be recognized within a message, and will not display nor count as a mention.

All of these methods store the key or fingerprint on the server as a *transient identity*.
### Invites

Instead of using a user ID, users may also join directly via an invite. Invites can be **shared via HTTPS link, QR code, or just invite code**. An invite link is similar to a Link URL, meaning that it embeds the target server, the target node link URL, the target project/planet, and the invite code.

Invites can be configured by the planet or project's administrators:
- **Maximum usage** of the invite link can be configured, from `1` to unlimited uses
- **Approval** can be required for an invite link or globally across all invites
- A **time limit** can be configured for each link, the default expiration time is a week
- The **default role** granted by the link. Normally, this is role 0 (guest user), but additional roles can be added. For safety reasons, invite links *cannot give administrator permissions (in any form, through Founder, or through a high enough role)*.

> [!example]
> An invite link could take the shape of:
> - `https://pet.app.scpija.com/aFzf291vc` (centralized shortlink)
> - `https://pet.app.scpija.com/join/myserver/fc21fmaxF` (server-bound shortlink)
> - `pet://server.example/join/d13FzscAAf` (petlink)

#### Single-sign-on (SSO)

A company may desire to connect their existing single-sign-on (SSO) infrastructure to PET, to automate invites. In this case, an invite link can be created, such as `pet://server.example/join/sso` or `pet://server.example/join/{invite_code}/sso`, which will redirect users to the organization's sign in provider.

This can be configured by the server or planet administrator, and generally, on self-hosted PET instances, should be configured directly within the server.
### First connect

On first connect with the server, a few things need to happen. First, if this is the first time you're joining a planet on a server, the server does not know about you yet. It will need to know your public key (in case the server only knew you by fingerprint), and it will also need you to sign the key with the sudo key.

What this means, in short, is that **joining a new server for the first time prompts for your password** as you need to be in sudo mode to join a new server. This is done so the server can know about your sudo key for potential later key rotations, and also so an attacker with only your private key can't join servers for you.

Once a server has this basic information, it will also request profile information, such as your *username* and your *profile (avatar, bio, etc)*.
### Leaked public key

If someone has your public key, the worst outcome for you is if you have notifications enabled, and they spam you with invitations in case they have your *Homeserver ID*.

A leaked public key will let anyone add you to their project, but as *transient identity*, which may expire^[Default value for the release build is to be determined, it will be configurable by the user.], and will not appear unless you actually open the project at least once.
## Key rotation

Key rotation is based around **sudo mode**, which uses the derived password-protected sudo key to protect your account in case your private key is compromised, so an attacker cannot rotate your keys and sign you out.

The old key and the sudo key both sign the new public key, which is propagated to every server your client knows of. In case a server is offline during that broadcast, or the client did not know about one of your servers, it will not rotate the key until you reconnect to it. This means you will have to enter sudo mode again to connect with the server.

**Rotating keys sign you out of every device** immediately, and also acts as revocation. If a server knows you with a new key, it will request you use the new key if you attempt to use the old one, and will not let you continue until you do so.

If your device gets stolen, the **sudo password will prevent them from rotating first**, and doing a rotation will sign them out.
## Recovery

As your identity is stored as your private key and sudo key, you need to store these two keys safely. When creating an account, you are automatically given a recovery passphrase, which will let you recover both keys. Anyone with this recovery passphrase can immediately trigger sudo mode as well, as it bypasses the password protection which is normally used to derive the sudo password itself.

> [!note]
> The technical reason behind the passphrase being master key, is that the risk of account loss with self-managed keys is really high, and we collectively decided a backup was more important.
>
> This comes with a warning message that this key grants full access to the account with no safeguard.
> 
> This warning lets user switch to a "strict recovery phrase", which does not bypass sudo, but comes with a warning that a lost sudo password leaves the account as a zombie.
> 
> A third option, shamir splitting, is also proposed in a dropdown next to the recovery type switch button.

On a homeserver, the key is stored securely there, and it is assumed users trust the homeserver with key management if they decide to create an account there. a user can always rotate keys out of a homeserver.
## Homeserver trust

As mentioned previously, **homeservers are trusted servers that hold your private key and can act on your behalf**. This is explicitly indicated on first sign-up, and this is for various convenience purposes such as background caching, push notifications, etc.

The homeserver (nor the client) **never store the sudo key** as it is derived on the spot when it is used and only ever stored in RAM or in the secure recovery passphrase.

The implications of this is that *a malicious homeserver can impersonate you*, however, they are still limited by the sudo key, so they can't rotate keys for you or join servers for you.
## Client key storage

On the client, keys are stored as secure [CryptoKey](https://developer.mozilla.org/en-US/docs/Web/API/CryptoKey) objects within [IndexedDB](https://developer.mozilla.org/en-US/docs/Web/API/IndexedDB_API). They can sometimes be exported for account backups. **The sudo key is never stored**.

To avoid XSS (and specifically self-XSS attacks, such as pasting code in the console), there is an anti self-XSS console warning in the client, and every use of embedded HTML is filtered for elements that may cause an XSS attack.
## Encryption

Encryption using the WKI keypair is used all the time, for various purposes:
- **Transport**: In sudo mode, all messages must be encrypted, while normal mode messages may be encrypted during transport (but that is not a strict requirement, as in normal mode, the only requirement is that the message is signed).
- **Storage**: Homeservers use the WKI keys to encrypt the stored user data with the key. Some projects can also be stored exclusively in sudo mode, in which case the data is completely end-to-end encrypted.
## Personal Access Tokens (PATs)

Personal Access Tokens are JWT tokens that authorize an HTTPS client to perform certain actions on behalf of a user.

These tokens are specifically created for one server, or on the homeserver for global access. *Note that servers can refuse to authorize re-routed actions over PATs that come from a homeserver.*

The point of the PATs is that they permit a lighter client to interact with a simple, HTTPS REST API to perform tasks on behalf of a user without re-implementing the entire WKI specification.

**Personal Access Tokens are scoped**: they can authorize only certain parts of the API, only on certain planets or node, or run with lower roles than your user.

The tokens also have an expiration date by default, however this can be turned off.

> [!tip]
> **Project/Planet Access Tokens** are similar in function and form, but are not bound to a user, instead bound to a planet or project directly. This lets an external client perform actions as a bot on the planet or project. The planet or project administrators decide of the scope they are allowed to access, as well as the roles they are given.
> 
> These bots can also be added using OAuth links.

# The Graph

The most important data structure in the PET project is the graph itself. It **contains absolutely everything**, from the simple message within a thread, to a picture stored as resource, to actual tasks and notes.

## Nodes and Edges

The PET graph is a conventional graph, made of two components. First, the **nodes**, the primary structure containing most of the graph's content information, and then both **edge** types.

> [!note]
> These graph components may act differently within a Lone Satellite graph, as the shape of the graph is partially dictated by external factors, such as the integration's API.

### Node

A **Node** is the most basic structure in the graph. It's a simple structure made of a few fields:

| Field name | Field type | Description                                                                          |
| ---------- | ---------- | ------------------------------------------------------------------------------------ |
| `id`       | `uuid4`    | The node's unique identifier.                                                        |
| `type`     | `string`   | The node's type. This is a string containing the class name, like `Node` or `View`.  |
| `name`     | `string?`  | The optional name. This name is displayed in the graph. Some nodes don't need names. |
Every single new node type inherits this simple structure, including `View` and all of its subtypes.

### Hard edges (Child nodes)

Hard edges are the main kind of edge, and represents a **structural relationship**.

Hard edges are just fields containing pointers (IDs) to the child node(s) associated with this field. There are two kinds of child-parent relationships:
- **Top-down relationships**: Mainly used when there are not a lot of child nodes. A top-down relationship is a pointer (or list of pointers) to child nodes.
- **Bottom-up relationships**: Used when there are lots of child nodes, meant to be used for queries

> [!example]
> For example, with `Thread`, this would be a *top-down relationship*:
> 
> | Field name | Field type             | Description                             |
> | ---------- | ---------------------- | --------------------------------------- |
> | `messages` | `Message*[] (uuid4[])` | The list of messages within the thread. |
> 
> While with `Message`, this would be a *bottom-up relationship*
> 
> | Field name | Field type        | Description                                 |
> | ---------- | ----------------- | ------------------------------------------- |
> | `thread`   | `Thread* (uuid4)` | The thread this message is associated with. |
> |            |                   |                                             |
> 
> In this case, you would prefer using a bottom-up relationship, as using a top-down relationship would make `Thread` heavy, while in bottom-up you only need to query messages with a matching thread. You generally prefer top-down relationships in most other cases, such as a `Task` pointing to a list of `Tags`.

### Soft edges

A soft edge is a secondary kind of edge, and represents a **semantic, non-structural relationship**. In short, this kind of relation means little to PET, but instead means more to the user itself.

Soft edges are represented as a separate structure, instances of a first-class type dedicated for them. Soft edges are by default bidirectional (but this can be changed on the soft edge field itself), completely free-form (technically, any two nodes can be bound together, and there is no restriction on circularity) and they carry a type with them.

> [!example]
> Here's what an example soft edge looks like (simplified example, only the important fields are annotated in this example):
> 
> | Field name | Field type             | Value | Description                             |
> | ---------- | ---------------------- | ------- | -------------------------------- |
> | `from` | `any* (uuid4)` |  `410c6c50-e413-4440-b202-b40b6400153c` | The source node. In this example, it is a `Note` node. |
> | `to` | `any* (uuid4)` |  `ff6c35a8-5354-43ee-9c9a-ebde9f453bac` | The target node. In this example, it is a `Task` node. |
> | `type` | `string` | `"pin"` | The type of link. Here, it is "pin", which means pin the note to the task. |
> This describes a semantic, visual link for the user, but doesn't affect behavior of any of the two nodes.

## Conflicts

The main graph itself is synchronized across devices, and resolved as a CRDT (Conflict-free replicated data type). Individual node contents, when heavy or when supporting live editing (such as editing a note or a word processor text document) uses its own individual CRDT style data structure.

The actual graph is resolved using some very light conflict resolution. The algorithm used for the graph itself is a "Last Write Wins" structure (specifically, for each metadata field of each node), although removed items are resolved as tombstones, with a time limit for garbage collection.

> [!note]
> While the graph itself uses a "Last Write Wins" structure, large node types with their own syncing systems may use any conflict resolution. LWW only applies to raw node metadata.

### Validation and concurrency resolution

Concurrency is handled by lamport timestamp and an UUID tiebreak. Cyclical moves are dropped with a notice.

Servers have the final authority when it comes to synchronization and can reject any and all conflicting, impossible, unauthorized or badly requested merge requests.
## Linking

One of the massive strengths of PET is its use as an **aggregator**. This means linking nodes from various satellite integrations, planets and projects, and embedding them as links in your current graph.

> [!tip]
> The first time you create a homeplanet on PET, the main view is an aggregation view of your tasks and events from across planets, calendars and integrations, and this is done entirely using links and *observatory API* queries!

### Node link URLs

Links take the form of `pet://` URLs.
Here are the components of this URL explained in detail:

```
pet://server/{planet}/[project_id]/{node_uuid}[?type=&auth=&...]
```

| Component name          | Description                                                                                                                                                       |
| ----------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `planet` (mandatory)    | The UUID or name of the planet / satellite to read from.                                                                                                          |
| `project_id` (optional) | The UUID or name of the project to read from within the planet or satellite.                                                                                      |
| `node_uuid` (mandatory) | The UUID of the node to read from.                                                                                                                                |
| `type=` (option)        | The expected node type to read. This validates the accepted type.                                                                                                 |
| `auth=` (option)        | A string describing the requested auth method. Can be `"key"` (the default, normal WKI auth), `"token"` (token authentication) or `"public"` (no authentication). |
### Linking rules

Whenever a link is used, it appears in the graph exactly as the target node. For example, linking to a `File` node will attempt to resolve the file and let you edit it just like any other `File` node. However, some exceptions arise:
- **The link may not resolve because of network failures**: in this case, the node will appear instead as an `UnresolvedRepresentation` node.
- **The link may not resolve because of permission/auth issues**: in this case, the node will appear as a `DeniedRepresentation`.
- **The link points to another link**: the link will reject the request with an `UnresolvedRepresentation`, unless multi-hopping is allowed in that specific link node.
- **The link points to another `BadNodeRepresentation` node**: The corresponding `BadNodeRepresentation` subclass is provided instead, but the link completes as if it resolved and will be marked as resolved from a *Link API* stand point.

## Roles

In PET, roles are similar to Matrix power levels in the fact they are associated with a power value. The creator of each project/planet is granted a special founding power (represented internally as `-1`, the Founder role) which grants them all permissions on the entire project/planet.

The base role (no role on the person) starts at a power of `0`. Role power value range between `1` and `2147483647`.

### Role Permissions

Roles are mainly used to grant top-level permissions over a project or team. For example, a role can grant top-level and global permissions such as "Modify project name and avatar", "Modify project settings", or "Manage other users' messages".

To tweak permissions on an individual node or node group level, you may use a permission controller node, the `PermissionController` node, which assigns UNIX-like permissions to nodes, and defines a new permission scope for other permissions. The permission system regarding those is detailed in the Core module section.

### Node behavior

Nodes are subject to permissions dictated by roles. Below is a table of causes and consequences related to node behavior and roles.

| Action taken (cause)                                       | Response (consequence)                                                        |
| ---------------------------------------------------------- | ----------------------------------------------------------------------------- |
| Access to a node without the `read` permission.            | The node returned is an instance of `DeniedRepresentation`.                   |
| Attempt to write to a node without the `write` permission. | Client prevents action; if called on the server, the server returns an error. |

### Founder role

The owner of a planet or a project gets the hidden Founder role in the associated graph. This role can be transferred and shared, but not removed. If the only remaining Founder attempts to leave a project, they have to transfer ownership or delete the project (this is analogous to the Server Owner on Discord).

The Founder role comes with internal ID `-1` (`ROLE_FOUNDER`) and has all permissions on the project and all its subnodes regardless of what their other roles are set to. 

## Satellites

On PET, integrations to other applications are called Satellites (to follow through on the spatial theme of the app). Satellites come in 2 major types, which differentiates them by the scale of the integration:
- **Lone Satellites** are satellites that are on the top-level, similarly to planets. These satellites have their own graph, with their own nodes, which proxy requests to APIs or external sources.
- **Orbiting Satellites** are local integrations within a planet or a project. They live within a graph, and spawn proxy nodes within that graph (for example, a GitHub orbiting satellite linking a PET project to a repository's issues would spawn `Proxy<Issue>` type nodes. See *Core module* for information about `Proxy` and template nodes.)

# Features

In order for the PET project to work, simply storing the graph and providing views is not enough. Systems for identity management, navigation, configuration and more have to be taken into account. This is what this section is about.
## Login

The log-in system within the PET application is the page that lets users sign into their account or create a new account from scratch.

There are multiple ways to sign into an account:
- **Sign in to a homeserver with classic authentication**: Here, classic authentication refers to password authentication, which is exclusively managed by the homeserver. This method isn't considered as safe as using the key directly, but it is an acceptable compromise to mesh in with existing tools like password managers.
- **Sign in by importing the key**: The key will be loaded into your client; if it is meant to belong to a homeserver, the client will automatically connect to the server to fetch and merge homeplanet contents.
- **Sign in by clicking on an already loaded key**: If the key is already in your CryptoKey storage, then it will show up in the interface by itself and clicking on it connects to the server, or if the key doesn't belong to a homeserver, loads and decrypts the homeplanet content from storage.
- **Sign in by importing the recovery phrase / backup file**: This automatically signs you into your account in sudo mode. If you are loading a backup, you will be prompted to revert to that backup if existing data is found.

Because WKI is a decentralized framework, signing up is also different.
- Users can create a **local account**, where the key is generated in the browser and must be backed up to continue, and where all the data is stored in the client.
- Users can connect to a homeserver and create a **homeserver-bound account**, in which case they will have to confirm they trust the server and acknowledge impersonation risks.

Users will then be asked to enter a username, a sudo mode password, and if the homeserver allows it, a password for classic authentication.

## Navigation

Navigation around the PET app is mainly based on a universal sidebar. This sidebar is always present but can be collapsed, and it's divided into three sections:
- **The sidebar header**: Shows the current planet/project banner, with its name on top. This section is responsible for providing you a button to configure the planet/project via a context menu. It also is useful to navigate back to a planet when within a project, as it displays a back link.
- **The sidebar item list**: Looks similar to a Discord channel sidebar. On projects, this shows the project's enabled views, with the pinned ones at the top. Views can be grouped together, dragged and shuffled around, and separators can be inserted. On planets, this shows the planet's active projects, and the planet's global views. Some items of this sidebar can be expanded (like pinned directories, projects...), making it look more like a directory tree. Groups can also be collapsed.
- **The user panel**: A panel located under the sidebar that shows the current user, and, on click, opens the general configuration menu for the user. See the *Settings* section for more information.

Additionally, from a planet, a link to the Planetarium is provided. See the *Planetarium* section for more information.

This sidebar can also have to its left a **bubble bar** if enabled by the user, similar to a Discord server list, which lists planets into clickable bubbles, homeplanet on top. Enabling the bubble bar moves the planetarium link to a special, tab-shaped bubble at the very top of the bar.
## Homepage

The PET homepage is a pinned view within the homeplanet. It is the first page you see in the app, and it is implemented as a transparent, non-movable **Canvas** with pre-programmed task and event aggregation widgets that pull over the *observatory API*.

It is the only view in the app, except for the Planetarium, that cannot be split or moved to a floating window.
## Planetarium

The Planetarium is the page where you **can zoom out from your planets and see every single one of them floating around in space**. The Planetarium renders star systems and floating planets in a space-like void where the user can pan and move, and it highlights places where important events are ongoing, or urgent tasks are to be done.

In the planetarium, a star system is simply a group of planets.

This can be seen as an alternative aggregation view to the homepage, but with the added benefit of displaying everything and navigating anywhere in a single click.

> [!note]
> The Planetarium always opens fullscreened, and floating windows fade out. They will return after exiting.

## View panel

One of the main features of PET's node graph are the **view nodes**, which provide an interface for the browser to render.

When opening a view, it will display **on the main content block of the app**, generally to the right of the sidebar. This view can be of any kind, as its contents are dictated by the node in question.

Multiple views can be on the screen at once, either using a tiled WM style, or using floating views, which are just views popped out into floating windows.

> [!tip]
> When manipulating a floating view over a canvas, it is possible to drop it into the canvas by pressing the pin button. Doing so will place the view inside the canvas in a persistent manner.

> [!important]
> Here are a few quirks of the view system:
> 
> - Some nodes are not directly views but associated with views, in which case, the rendered content will use the associated virtual view, and they will not appear in the sidebar permanently, only while viewing.
> 
> - A crashed view cannot break the app, instead, the app switches to the internal `CrashView`.
> 
> -  Views can (and are intended to) nest each other deeply. For example, a `Thread` node showing its content via the `ThreadView` view embeds all its `Messages` within nested, immovable, borderless `MessageSubView`.

## Planet and project management

Configuring a planets or projects is a critical component of the interface, as these settings allow users to invite others to their planets, configure roles and permissions, and manage security options, among other things.

Accessing the planet or project configuration is done via the **sidebar header**, within the context menu.

This menu lets you:
- **Configure naming, avatar, and other information**: With sufficient permissions, a user can configure the name and the avatar of the planet or project.
- **Manage members**: See pending approvals, banned users, members and their roles.
- **Manage invites**: Invite new members, revoke or edit existing invite links.
- **Manage roles and power levels**: Manage role creation, select their power level, and select their baseline permissions.
- **Manage permissions**: Using the permission manager, a user can select baseline permissions for all roles or select roles.
- **Transfer ownership**: The owner of the planet or project can transfer or duplicate their ownership status of the planet via the Founder role.
- *And more!*
  
> [!danger]
>  Granting Founder permissions to someone grants them the permission to **delete the planet/project, remove all other owners, and kick users**. Make sure you trust anyone you give this special role.

### Managing permissions on nodes

To manage permissions on a specific node:
- If you are looking at a view present in the sidebar: you should be able to right click the view and select "View Settings" to open the settings menu.
- If you are looking at a view not present in the sidebar, the view should have a window header/frame. Clicking the triple dots and selecting "Node Settings" will open the settings menu.
- Once the settings menu is open, toggle "inherit permissions" to off. Congratulations! You can now configure this node and all of its descendents.

This internally creates a `PermissionController` transparent wrapper. Having a `PermissionController` adds a "Permissions" tab on the node settings. Tuning the option "inherit permissions" off creates it, and turning it on deletes it (tombstones).

## Settings

The settings menu is placed under the sidebar at the bottom left of the screen (or right if the sidebar is on the right). Clicking on the user profile opens the settings window in the center of the screen.

The settings displays configuration pages grouped in tabs (vertical tabs on the left of the settings window). The list below is in the same order as in the application.

- *Account*
	- **Profile and Identity**: User profile customization (username, avatar, biography, etc.) and key management (import, export, transfer, rotate...)
	- **Data Management**: Manage stored data (locally or on the homeserver), create backups
	- **Personal Access Tokens**: Manage personal access tokens.
	- **Privacy**: Manage shared data.
	- **Integrations**: Manage PET integrations and connected OAuth applications.
- *Experience*
	- **Notifications**: Manage notifications, such as push or webhook notifications.
	- **Accessibility**: Various accessibility settings: high contrast, reduced motion, navigation...
	- **Theme**: Pick themes, customize interface sizing, adjust theme parameters, etc.
	- **Keyboard bindings**: Manage keybinds used within the app.
- *Extras*
	- **Collection**: Control gamification, select backgrounds and cosmetics, buy new unlocks, cosmetics or backgrounds with credits, see achievements, etc.
	- **Assistant**: Manage the assistant, select the character or turn the feature off.
	- **Help & About**: PET version and link to documentation.
- *Project features*
	- (Per-module global settings)

## Assistants

One of the main motivational and comfort features of PET is to provide little virtual assistant character that give a little bit of character to the UI.

The main idea is that these characters are here in places where the UI suggest autonomous action and decision making.

For example, when reviewing the tasks to do, one of the accessible features to provide is the "Pick for me" option, which picks an available task at random and presents it as what to do. This can be useful in situations where someone is unable to decide. In this example, the assistant would be the one providing this feature, with unique dialogue lines for each of the assistant characters.

The dialogue is all hand-written, and they often replace gray option boxes with a slightly more fun variant.

It is meant to be encouraging and to give extra character to every reminder, notification, and nag (like, for example, backup reminders) as it is easier to attach yourself to something that looks alive.

> [!note]
> Most of the assistants are cat-like anthropomorphs in sci-fi spatial exploration gear, and represent real-life cats. There may be other characters/species in the future, but each is planned to have their unique art and personality.

## Gamification

PET as a platform has for one major goal of improving productivity, but it may be hard for some people to simply just start going. **To help, PET includes opt-in gamification** if users want the application to try and motivate them.

> [!warning]
> PET is a non-profit project and does not seek profits by means of microtransactions. The rewards exclusively come out of completing tasks and doing work *outside of PET*, as the application attempts to make its users engaged in their work, and not on the app.
> 
> This segment of the application uses human psychology to help some people work, but it may be distracting for others, which is why this segment is *opt-in*.

Among the gamified aspects:
- **Completing tasks grants shop credits**: This shop is a segment in the settings page, containing mainly cosmetics, but it may serve as a little incentive to do more. Spamming tiny tasks is not rewarded.
- **New assistant cats and new skins for them can be unlocked**: Unlocks are done through the shop.
- **Exclusive planet backgrounds**: Unlocks are done through the shop.
- **Exclusive themes**: Unlocks are done through the shop.
- **Achievements**: These achievements are granted by completing projects, tasks, and more.
- **Streaks**: Performing tasks consistently shows up as a streak.
  > [!warning]
  > As a feature, *streaks* can be problematic or a source of stress for people with anxiety or ADHD. As a result, this feature is also opt-in.

## Accessibility

PET is meant to be an accessible platform for everyone, including those who need the applications they use to adapt to their needs, and here, the main demographic is people with anxiety disorders, ADHD, and other related conditions. For more information, visit [MDN's page on cognitive accessibility](https://developer.mozilla.org/en-US/docs/Web/Accessibility/Guides/Cognitive_accessibility)

Options like "pick for me", short-and-fast communication and such systems are intended to be put into place, as well as different visual modifications to make interface more readable or more-or-less information-packed, for example.

Additionally, PET will strive to be an accessible platform for people with visual or motor impairment, such as providing color blindness options, higher contrast, remapping of controls to accessibility device, changing the app scaling, providing consistent [ARIA](https://developer.mozilla.org/en-US/docs/Web/Accessibility/ARIA) roles and following [WCAG](https://developer.mozilla.org/en-US/docs/Glossary/WCAG) guidelines.

## Developer tooling

For developers, the `nekocmd` global object is a helpful tool for debugging hinted at in the anti self-XSS warning in the browser console. This tool will not let you manage keys, but it will help you debug custom views, workflows, and more. It exposes a lot of the PET internals, and its commands can be revealed via the `nekocmd.help()` function call.

Logs are tagged per component using a custom logging system. This uses console log styling.

# Planned node types and views (Feature wishlist)

Below is a list of all the planned node types and views that are planned for future implementation. Not all of them will be implemented quickly or in the first releases.

---
## Core module

>[!info] Dependencies
> Every module listed on this page depends on this module, the Core module.
> Modules on this page are **sorted in dependency order**, so a module cannot depend on modules after its definition.
> 
> On the development side of things, modules may depend on each other, however early module implementation of non-critical parts may be stubbed with `NIRepresentation` nodes (see below). **On equal dependency level, the modules are sorted by priority**.

The core module contains every node and view type only relevant to the basic functionality of the program.

>[!hint] Node markers
> Before each node definition, you may find a marker in parentheses.
> - Node types marked `virtual` can't be stored in the graph and serve other purposes.
> - Node types marked `interface` can't be stored in the graph, but can be inherited from, and exist to provide a common interface between modules or for a view.
> - Node types marked `template` wrap over other types dynamically. These types are mainly used to proxy existing types to different APIs, such as `Proxy`, by adding getters and setters on the fields. This document annotates the template parameters in a C++ style (for example, like `Template<Type>`).
> - Node types marked `encapsulated` are not part of the graph, but are part of a graph node (for example, a widget within a canvas). This lets them be rendered by integrating the view code instead of embedding it, making it part of the current document.
> - Views marked `parametric` vary slightly based on input parameters, which can be provided when embedded. Some parametric views also allow other view declarations to modify their behavior after first declaration.

> [!danger] Node permissions on `PermissionController` nodes
> Permission controller nodes allow to change **any top-level permission locally**.
> Additionally, permission controllers can **directly change access permissions**, which is described below.
> 
> Access permissions on nodes are split into three main switches:
> - `read`: Permission to read the node contents.
> - `write`: Permission to write to a node.
> - `execute`: Permission to execute code, trigger workflows.
> These switches emulate UNIX permissions on files and directories.
> Access permissions apply to 3 categories of users: 
> - `owner`: The owner of the file.
> - `group`: The minimum permission designated power (See Roles). This is usually `1` by default, but can be set to any power value.
> - `everyone`: The permissions for everyone with access to the graph.
>   
>   When a node has multiple `PermissionController` parents, the `read` permissions use the least restrictive parent, while the `write` and `execute` permissions use the most restrictive.

**Nodes**
- [ ] `Node` and its following subtypes:
	- [ ] `CustomNode`: Represents a node with extra or unknown behavior.
	- [ ] `LinkNode`: Represents a node from another graph. Links are resolved over special `pet://` URLs.
	- [ ] `PermissionController`: Passthrough nodes which imposes permission restrictions or modifications.
	- [ ] (interface) `View`: Represents a view over other nodes, through a selector.
	- [ ] (interface) `Resource`: File Resources.
	- [ ] (template *over type*) `Proxy`: A passthrough wrapping template that adds getters and setters over a node, and potentially alters its behavior. Mainly used to route read or write calls to an external API, these are often generated by satellite integrations. 
	- [ ] (virtual) `BadNodeRepresentation`: A virtual node type representing every invalid node, such as unresolved `LinkNodes` or unknown node types.
		- [ ] (virtual) `UnresolvedRepresentation`: A link node whose link resolution failed.
		- [ ] (virtual) `DeniedRepresentation`: A node you don't have the permission to `read`.
		- [ ] (virtual) `NIRepresentation`: This feature is not implemented. Used internally for development. Nodes may use this response as a way to disable feature flags. For example, a `Canvas` may find `Workflow` not implemented, and thus the feature will be grayed out in the editor.
**Views** (inheriting from `View`)
- [ ] (virtual) `GraphView`: The base graph view. This is what `View` is represented as by default.

---
## Automation module
On PET, automation is done using Workflows, a specific kind of node that provide a visual, node-based editor for general automations around the app. Using workflows, users can link up multiple project and planets together, and make custom views by adding them inside of canvas.

Workflows are flowchart-like graphs of nodes, which are of pre-defined types by each module (like the Core-flow API, declared by the Core module, which allows modification of nodes). Users may not run arbitrary machine or javascript code on the client or server.

Each flow run is done in its own, individual context, and can't interfere with other flows (unless there is an existing, intentional IPC API or process control API declared later on). APIs are permission gated as well, meaning permissions may be required to run certain flow blocks.

> [!note] Server flow budgeting
> Server-run workflows may be restricted by both the server admin, and the project/planet owner. The limitations can be set in steps, time, or both.

**Nodes**
- [ ] `Workflow`: Contains the automation flows.
**Views** (inheriting from `View`)
- [ ] (virtual) `WorkflowView`: The workflow editor.

---
## Calendar module
The Calendar module tackles anything that has to do with event planning.

**Nodes**
- [ ] (interface) `Event` inherits from `Node`. It represents a basic calendar event, with a start and end, importance, RSVP, invites and more. It includes the following subtypes:
	- [ ] `CalendarEvent`: a simple event with all of the `Event` features.
	- [ ] `CalendarDeadline`: a specific point in time, essentially an `Event` with no end, used to mark deadlines.
	- [ ] `CalendarRange`: a range over time that isn't truly an "event" but more of an overlay marker.
**Views** (inheriting from `View`)
- [ ] `CalendarView`: A view aggregating `Event` nodes in a normal calendar format.
- [ ] `TimelineView`: A view aggregating `Event` nodes in a timeline/waterfall format.

---
## Thread module
A thread is a place to discuss about a topic. For example, a thread attached to a message in a channel lets people discuss that specific topic in more detail, or a thread attached to an issue or task lets contributors discuss it before moving on.

**Nodes**
- [ ] `Thread` inherits from `Node`
- [ ] `Message` inherits from `Node`
- [ ] `Attachment` inherits from `Resource`
**Views** (inheriting from `View`)
- [ ] (virtual) `ThreadView`: The thread view, a text/messaging interface.
- [ ] (virtual) `MessageSubView`: A view plugin over an individual message.

---
## Memo module
A memo is a team-wide note meant to be acknowledged. For example, it may be about a policy change, a scope change, or it may simply embed a poll to collect opinions.

**Nodes**
- [ ] `Memo` inherits from `Node`
**Views** (inheriting from `View`)
- [ ] (virtual) `MemoView`: A view representing an active memo.

---
## Tasks module
A Task represents a real task to be completed.

**Nodes**
- [ ] `Task` inherits from `Node`
- [ ] `Milestone` inherits from `Event`
- [ ] `Iteration` inherits from `CalendarRange`
**Views** (inheriting from `View`)
- [ ] (virtual) `TaskView`: The view associated with each `Task` in the user interface.
- [ ] (parametric) `TableView`: A view displaying tasks in a table
- [ ] (parametric) `KanbanView`: A view display tasks in various columns
- [ ] (parametric) `DependencyView`: A view displaying tasks relative to their blockers
- [ ] (parametric) `TreeView`: A view displaying tasks in a tree
- [ ] (parametric) `MilestoneView`: A view organizing tasks in "Milestones" which depend on other tasks.

---
## Note module
A note (sticky note) is a little note attached to another node. You could pin a note over a file to add some context, for example.

**Nodes**
- [ ] `Note` inherits from `Node`
**Views** (inheriting from `View`)
- [ ] (virtual) `NoteView`: A view representing a note.

---
## Collection module
A collection groups items together. This means the items are considered to be "close" and semantically associated.

**Nodes**
- [ ] (interface) `CollectionInterface` inherits from `Node`
- [ ] `Collection` inherits from `CollectionInterface`
**Views** (inheriting from `View`)
- [ ] (virtual) `CollectionView`: A view representing a tiled representation of the contents.

---
## Canvas module
Canvases are useful, self-viewing nodes where information can be laid out in custom formats. A canvas contain a main text body (think obsidian-style Markdown), and widgets such as text boxes, buttons, images, and embedded views or filtered views to other parts of the graph. Canvases may also contain Workflows, which allow users to make them dynamic.

>[!info] Dependencies
> This module depends on **Automation**, but will work if it is stubbed.

**Views** (inheriting from `View`)
- [ ] `Canvas`: A canvas. This is an explicit node, like a `CalendarEvent` or a `Task` (which means it is treated like data and not like UI), but it also is a view, meaning it is revealed in the project sidebar by default.
- [ ] (encapsulated interface) `ContentWidget`: A canvas content widget. This element is encapsulated, meaning it's stored inside the `Canvas` as structured data, and not inside the graph itself.
- [ ] (interface) `EmbeddedWidget`: A canvas embedded widget. Like a widget, except it's visible in the graph and is within its own embed box. These widgets can be used as rich message content.
- [ ] `WidgetExport`: A special widget made to export one or more widgets. Think of it like a blank `Canvas` with a fullscreen widget.

---
## Widget module
Widgets are tiny, self-viewing nodes that are pre-programmed to do something. They are intended to be used within Canvas, and the embedded widgets are also intended to be used as part of rich text, such as within a message, memo, or post.

>[!info] Dependencies
> This module depends on **Canvas**.

> [!warning]
> This module is not complete and it may contain plenty of nodes in the future.

**Content Widgets** (inheriting from `ContentWidget` within the Canvas module)
- [ ] `TextWidget`: A floating text block.
- [ ] `ImageWidget`: A floating image block.
- [ ] `DrawingWidget`: A whiteboard drawing section.
- [ ] `SVGWidget`: An embedded SVG drawing.
- *In the future, this may be expanded...*
**Embeddable Widgets** (inheriting from `ContentWidget` within the Canvas module)
- [ ] `ClockWidget`: A clock. Can also be a timer or a stopwatch.
- [ ] `PollWidget`: A single-choice, or multi-choice poll.
- [ ] `CalendarPollWidget`: An availability poll: The author selects time slots (or leaves it blank) and the users select their preferred time. Useful to organize a meeting.
- *In the future, this may be expanded...*

---

## Issue and ticket module
An issue or a ticket, like in Jira or on GitHub.

>[!info] Dependencies
> This module depends on **Task**.

**Nodes**
- [ ] `Issue` inherits from `Task`
**Views** (inheriting from `View`)
- [ ] (virtual) `IssueView`: inherits from `TaskView`, the actual view to represent the issue.

---
## Files module
This is a filesystem module: it lets users store files and directories directly within PET (as long as it stays within storage limits). These files can contain anything, and the module exposes the `FileEmbed` interface so the file preview can be turned into an editor by other modules.

**Nodes**
- [ ] (interface) `FileInterface` inherits from `Node`
- [ ] `File` inherits `FileInterface` and bundles `Resource`
- [ ] `SpecialFile` inherits from `FileInterface`
- [ ] `Directory` inherits from `CollectionInterface`
**Views** (inheriting from `View`)
- [ ] (interface) (parametric) `FileEmbed`: File view editor interface.
- [ ] (virtual) (parametric) `FileEmbedBasic`: A basic file viewer.
- [ ] (virtual) (parametric) `FileView`: A view representing a file, embedding a corresponding `FileEmbed` compatible entity
- [ ] (virtual) (parametric) `DirectoryView`: A view representing a directory (basic file explorer)

---
## Extra views module
This modules contains some useful views over the graph or parts of the graph. This gives more options to users on the information sorting topic. Usage on this pinned over a collection may be useful to group things into a sort of "common index".

>[!info] Dependencies
> This module depends on **most previous modules**, but it will still work on stubbed implementations.

**Views** (inheriting from `View`)
- [ ] `Corkboard`: A skeuomorphic view grouping the results of a graph query on a cork board, collections annotated with red string and pins with tacks.
- *In the future, this may be expanded...*

---
## File editor (File views) module
This module groups a bunch of `FileEmbed` extensions for specific files.

>[!info] Dependencies
> This module depends on **Files**.

**File embeds** (Views inheriting `FileEmbed`. All of these are `parametric` and `virtual`)
- [ ] `FileEmbedWord`: A word processor edition embed, for `.docx` and `.odt`.
- [ ] `FileEmbedSheet`: A spreadsheet edition embed, for `.xlsx` and `.ods`.
- [ ] `FileEmbedPresent`: A presentation edition embed, for `.pptx` and `.odp`.
- *In the future, this may be expanded...*

---
## Channel module

>[!info] Dependencies
> This module depends on **Thread**.

**Nodes**
- [ ] (interface) `Channel` inherits from `Node`
- [ ]  `TextChannel` inherits from `Channel`
- [ ]  `VoiceChannel` inherits from `Channel`
- From the *Thread* module, this uses `Message`, `Attachment`...
**Views** (inheriting from `View`)
- [ ] (virtual) `ChannelView`: A real-time messaging or call interface for a `Channel`.