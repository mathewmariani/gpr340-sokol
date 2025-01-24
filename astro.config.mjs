// @ts-check
import { defineConfig } from 'astro/config';

// https://astro.build/config
export default defineConfig({
    site: 'https://www.mathewmariani.com',
    base: '/gpr340-sokol/',
    srcDir: './website/src',
    publicDir: './website/public',
    vite: {
        resolve: {
            preserveSymlinks: true,
        },
    },
});