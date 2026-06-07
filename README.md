# Xuntian Rao Blog

This repository uses `master` as the maintainable source branch for the site. The old Hexo source history is still preserved on the `hexo` branch, but new edits should happen on `master`.

## Structure

- `source/_posts/`: blog posts in Markdown. Post images live in a matching folder under `source/_posts/`.
- `source/photography/`: photography pages. Each photo set is a Markdown page under `source/photography/<slug>/index.md`.
- `source/resume/`: the resume page source.
- `themes/xuntian/`: the current custom Hexo theme.
- `public/`: local generated output from Hexo. It is ignored by Git and should not be committed.
- `.github/workflows/pages.yml`: builds and deploys the site to GitHub Pages after pushing `master`.

## Local Development

```bash
npm install
npm run dev
```

The local Hexo server runs at [http://localhost:4000/](http://localhost:4000/).
`npm run server` and `npm start` are aliases for the same local preview command.

## Local Build Check

```bash
npm run clean
npm run build
```

`npm run build` generates a local preview build into `public/` and creates `public/.nojekyll` automatically.
`public/` is ignored by Git, so do not commit generated HTML.

## Deploy

Commit and push the source files to `master`:

```bash
git push origin master
```

GitHub Actions runs `.github/workflows/pages.yml`, builds Hexo on GitHub, uploads `public/`, and publishes it through GitHub Pages.

## Add A Blog Post

Create a Markdown file in `source/_posts/`:

```markdown
---
title: My New Post
date: 2026-06-08
tags:
  - note
---

Write the post here.
```

If the post has images, create `source/_posts/my-new-post/` and reference images from the post.

## Add A Page

Create `source/<page-name>/index.md`:

```markdown
---
title: Page Title
comments: false
---

Page content here.
```

## Change The Header Image

Put the image under `source/pic/`, then update `_config.yml`:

```yaml
theme_config:
  brand_mark:
    image: /pic/profile.JPG
    text: XR
```

If `image` is removed or left empty, the header falls back to the `text` value.

## Add A Photography Set

Create `source/photography/<slug>/index.md`:

```markdown
---
title: Photo Set Title
date: 2026-06-08
type: photo
cover: /photography/<slug>/cover.jpg
summary: One short line describing the set.
frame: Frame 06
camera_note: Natural light
frames:
  - image: /photography/<slug>/frame-02.jpg
    caption: Frame 02
comments: false
---

Photo notes here.

![A frame](/photography/<slug>/frame-02.jpg)
```

Put the images in the same folder. The photography index at `/photography/` will pick up pages with `type: photo`.
